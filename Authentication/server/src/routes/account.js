import express from 'express';
import asyncify from 'express-asyncify';
import nodemailer from 'nodemailer';
import dotenv from 'dotenv';

import Account from '../models/account';
import Verfication from '../models/verification';
import { checkEmailFormat, checkUsernameFormat, checkPasswordFormat } from '../modules/validation';

dotenv.config();

const router = asyncify(express.Router());

const userList = {};
let accessKeySeed = Math.random();

const generateAccessKey = () => {
    const accessKey = accessKeySeed.toString(36);
    accessKeySeed += Math.random();
    return accessKey;
}

const generateVerifyCode = () => {
    return Math.random().toString(36).substring(6);
}

const sendEmailVerifyCode = async (destination) => {
    const sender = process.env.EMAIL_ADDR;
    const pass = process.env.EMAIL_PASS;
    const host = process.env.EMAIL_HOST;
    const transporter = nodemailer.createTransport({
        service: host,
        auth: { user: sender, pass: pass }
    });

    const verifyCode = generateVerifyCode();
    try {
        await Verfication.findOneAndUpdate({ email: destination },
            { email: destination, verifyCode, isVerified: false },
            { upsert: true, setDefaultsOnInsert: true }
        );

        return transporter.sendMail({
            from: `Heroes<${sender}>`,
            to: destination,
            subject: '[히어로즈] 비밀번호 찾기 인증 메일',
            html: `<h1>이메일 인증 코드</h1><h2>${verifyCode}</h2>`
        });
    } catch (err) {
        throw err;
    }
}

router.post('/email/verify/request', async (request, response) => {
    const { email, isNewEmail } = request.body;
    if (!checkEmailFormat(email)) {
        return response.json({
            error: '유효하지 않는 이메일 주소입니다.'
        });
    }

    try {
        const account = await Account.findOne({ email });
        if (account && isNewEmail) {
            return response.json({
                error: '이미 존재하는 계정입니다.'
            });
        }
        else if (!account && !isNewEmail) {
            return response.json({
                error: '존재하지 않는 계정입니다.'
            });
        }

        await sendEmailVerifyCode(email);
        return response.json({
            message: '입력하신 이메일을 확인해주세요.'
        });
    } catch (err) {
        console.log(err);
        return response.json({
            error: "서버가 응답할 수 없는 상태입니다."
        });
    }
});

router.post('/email/verify/confirm', async (request, response) => {
    const { email, verifyCode } = request.body;

    try {
        const foundEmail = await Verfication.findOne({ email, verifyCode });
        if (!foundEmail) {
            return response.json({
                error: '유효하지 않는 인증번호입니다.'
            });
        }

        await foundEmail.updateOne({ isVerified: true });
        return response.json({ message: '인증되었습니다.' });
    } catch (err) {
        console.log(err);
        return response.json({
            error: "서버가 응답할 수 없는 상태입니다."
        });
    }
});

router.post('/help/account/search', async (request, response) => {
    const { email, verifyCode } = request.body;

    try {
        const foundEmail = await Verfication.findOne({ email, verifyCode });
        if (!foundEmail) {
            return response.json({
                error: '유효하지 않는 인증번호입니다.'
            });
        }

        await foundEmail.updateOne({ isVerified: true });

        const account = await Account.findOne({ email });
        if (!account) {
            return response.json({
                error: '올바르지 않은 요청입니다.'
            });
        }

        return response.json({
            username: account.username,
        });
    } catch (err) {
        console.log(err);
        return response.json({
            error: "서버가 응답할 수 없는 상태입니다."
        });
    }
});

router.post('/help/password/reset', async (request, response) => {
    const { email, newPassword } = request.body;

    try {
        const account = await Account.findOne({ email });
        if (!account) {
            return response.json({
                error: '올바르지 않은 요청입니다.'
            });
        }

        if (account.validateHash(newPassword)) {
            return response.json({
                error: '기존 비밀번호와 일치합니다. 새로운 비밀번호를 입력해주세요.'
            });
        }

        if (!checkPasswordFormat(newPassword)) {
            return response.json({
                error: '비밀번호는 8자 이상으로 숫자와 영문자의 조합으로 구성되어야 합니다.'
            });
        }

        await Verfication.findOneAndDelete({ email });

        const hashedPassword = account.generateHash(newPassword);
        await account.updateOne({ password: hashedPassword });

        return response.json({
            message: "비밀번호가 재설정되었습니다. 로그인 해주세요."
        });
    } catch (err) {
        console.log(err);
        return response.json({
            error: "서버가 응답할 수 없는 상태입니다."
        });
    }
});

router.post('/signup', async (request, response) => {
    const { email, username, password } = request.body;

    try {
        const foundEmail = await Verfication.findOne({ email });
        if (foundEmail == null || !foundEmail.isVerified) {
            return response.json({ 
                error: "이메일 인증이 필요합니다." 
            });
        }

        if (!checkUsernameFormat(username)) {
            return response.json({
                error: '5~20자의 영문, 숫자의 조합만 사용 가능합니다.'
            });
        }

        if (!checkPasswordFormat(password)) {
            return response.json({
                error: '비밀번호는 8자 이상으로 숫자와 영문자의 조합으로 구성되어야 합니다.'
            });
        }

        const account = await Account.findOne({ username });
        if (account) {
            return response.json({
                error: '이미 존재하는 계정입니다.'
            });
        }

        let newAccount = new Account({ email, username, password });
        newAccount.password = newAccount.generateHash(password);

        await newAccount.save();
        await Verfication.findOneAndDelete({ email });

        return response.json({
            message: '회원가입이 완료됐습니다. 로그인 해주세요.'
        });
    } catch (err) {
        console.log(err);
        return response.json({
            error: "서버가 응답할 수 없는 상태입니다."
        });
    }
});

router.post('/signin', async (request, response) => {
    const { username, password } = request.body;

    try {
        const account = await Account.findOne({ username });
        if (account == null || !account.validateHash(password)) {
            return response.json({
                error: '계정이 존재하지 않거나, 잘못된 비밀번호입니다.'
            });
        }

        const accessKey = generateAccessKey();
        userList[accessKey] = account._id;
        return response.json({ accessKey });
    } catch (err) {
        console.log(err);
        return response.json({
            error: "서버가 응답할 수 없는 상태입니다."
        });
    }
});

router.post('/logout', (request, response) => {
    const { accessKey } = request.body;

    if (!userList.hasOwnProperty(accessKey)) {
        return response.status(400).json({
            error: "doesn't exist account"
        });
    }

    delete userList[accessKey];
    return response.end();
});

router.post('/auth', async (request, response) => {
    const { accessKey } = request.body;
    const ErrorCode = {
        Unauthorized: 3,
        Conflict: 4
    };
    
    if (!userList.hasOwnProperty(accessKey)) {
        return response.json({ 
            errorCode: ErrorCode.Unauthorized 
        });
    }
    
    try {
        let usingAccessKey = '';
        for (var key in userList) {
            if(key == accessKey) continue;
            
            if (userList[key] == userList[accessKey]) {
                usingAccessKey = key;
                break;                
            }
        }

        if (usingAccessKey !== '') {
            delete userList[usingAccessKey];
            return response.json({
                errorCode: ErrorCode.Conflict,
                usingAccessKey,
                accountId: userList[accessKey]
            });
        }

        return response.json({
            accountId: userList[accessKey]
        });
    } catch (err) {
        console.log(err);
        return response.json({
            error: '서버가 응답할 수 없는 상태입니다.'
        });
    }
});

export default router;