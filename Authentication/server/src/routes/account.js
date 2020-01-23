import express from 'express';
import nodemailer from 'nodemailer';
import dotenv from 'dotenv';

import Account from '../models/account';
import Email from '../models/email';
import { checkEmailFormat, checkUsernameFormat, checkPasswordFormat } from '../modules/validation';

const router = express.Router();

dotenv.config();

const generateVerifyCode = () => {
    return Math.random().toString(36).substring(6);
}

const sendEmailVerifyCode = (to) => {
    const sender = process.env.EMAIL_ADDR;
    const pass = process.env.EMAIL_PASS;
    const host = process.env.EMAIL_HOST;

    const transporter = nodemailer.createTransport({
        service: host,
        auth: { user: sender, pass: pass }
    });

    const verifyCode = generateVerifyCode();
    Email.findOneAndUpdate({ email: to }, 
        { email: to, verifyCode },
        { upsert: true, setDefaultsOnInsert: true }, 
        (err) => { if(err) throw err; }
    );
    
    return transporter.sendMail({
        from: `Heroes<${sender}>`,
        to: to,
        subject: '[히어로즈] 비밀번호 찾기 인증 메일',
        html: `<h1>이메일 인증 코드</h1><h2>${verifyCode}</h2>`
    });
}

router.post('/help/password/reset', (request, response) => {
    const { email, newPassword } = request.body;

    Account.findOne({ email }, (err, account) => {
        if(err) throw err;

        if(!account) {
            return response.status(400).json({
                message: '올바르지 않은 요청입니다.'
            });
        }

        if(account.validateHash(newPassword)) {
            return response.status(401).json({
                message: '기존 비밀번호와 일치합니다. 새로운 비밀번호를 입력해주세요.'
            });
        }
    
        Email.findOneAndDelete({ email }, (err) => {
            if(err) throw err;
        });

        const hashedPassword = account.generateHash(newPassword);
        account.updateOne({ password: hashedPassword }, (err) => {
            if(err) throw err;

            return response.status(200).json({
                message: "비밀번호가 재설정되었습니다. 로그인 해주세요."
            });
        });
    });
});

router.post('/email/verify/request', (request, response) => {
    const { email, isNewEmail } = request.body;

    if(!checkEmailFormat(email)) {
        return response.status(400).json({
            message: '유효하지 않는 이메일 주소입니다.'
        });
    }

    Account.findOne({ email }, (err, exists) => {
        if(err) throw err;

        if(exists && isNewEmail) {
            return response.status(409).json({
                message: '이미 존재하는 계정입니다.'
            });
        }
        else if(!exists && !isNewEmail) {
            return response.status(401).json({
                message: '존재하지 않는 계정입니다.'
            });
        }
    
        sendEmailVerifyCode(email)
            .then(info => {
                return response.status(200).json({
                    message: '입력하신 이메일을 확인해주세요.'
                });
            })
            .catch(err => { if(err) throw err })    
    });
});

router.post('/email/verify/confirm', (request, response) => {
    const { email, verifyCode } = request.body;

    Email.findOne({ email, verifyCode }, (err, foundEmail) => {
        if(err) throw err;

        if(!foundEmail) { 
            return response.status(401).json({
                message: '유효하지 않는 인증번호입니다.'
            });
        }

        foundEmail.updateOne({ isVerified: true }, (err) => {
            if(err) throw err;

            return response.status(200).json({});
        });
    });
});

router.post('/signup', (request, response) => {
    const { email, username, password } = request.body;

    Email.findOne({ email }, (err, foundEmail) => {
        if(err) throw err;

        const message = "이메일 인증이 필요합니다.";

        if(!foundEmail) { 
            return response.status(400).json({ message });
        }

        if(!foundEmail.isVerified) {
            return response.status(401).json({ message });
        }
    });

    if(!checkUsernameFormat(username)
        || username.length < 5 || username.length > 20) {
        return response.status(400).json({
            message: '5~20자의 영문, 숫자의 조합만 사용 가능합니다.'
        });
    }

    if(password.length < 8) {
        return response.status(400).json({
            message: '비밀번호는 최소한 8자 이상으로 입력해야 합니다.'
        });
    }

    if(!checkPasswordFormat(password)) {
        return response.status(400).json({
            message: '비밀번호는 숫자와 영문자의 조합으로 구성되어야 합니다.'
        });
    }

    Account.findOne({ username }, (err, exists) => {
        if(err) throw err;

        if(exists) {
            return response.status(409).json({
                message: '이미 존재하는 계정입니다.'
            });
        }

        let account = new Account({ email, username, password });
        account.password = account.generateHash(account.password);

        account.save(err => {
            if(err) throw err;

            request.session.loginInfo = {
                _id: account._id,
                username: account.username
            };

            Email.findOneAndDelete({ email }, (err) => {
                if(err) throw err;
            });

            return response.status(200).json({
                message: '회원가입이 완료됐습니다. 로그인 해주세요.'
            });
        });
    });
});

router.post('/signin', (request, response) => {
    const { username, password } = request.body;

    Account.findOne({ username }, (err, account) => {
        if(err) throw err;

        if(!account) {
            return response.status(401).json({
                message: '계정이 존재하지 않거나, 잘못된 비밀번호입니다.'
            });
        }

        if(!account.validateHash(password)) {
            return response.status(401).json({
                message: '계정이 존재하지 않거나, 잘못된 비밀번호입니다.'
            });
        }

        request.session.loginInfo = {
            _id: account._id,
            username: account.username
        };
        
        return response.status(200).json({ 
            accountId: account._id, 
        });
    });
});

router.post('/logout', (request, response) => {
    request.session.destroy(err => { if(err) throw err; });

    return response.json({ success: true });
});

export default router;