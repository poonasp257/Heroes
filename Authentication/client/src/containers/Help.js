import React, { PureComponent } from 'react';
import axios from 'axios';

import { connect } from 'react-redux';
import { requestEmailVerifyCode, confirmEmailVerifyCode, expireVerifyCode } from 'modules/verification';
import { openDialog } from 'modules/dialog';

import Grid from '@material-ui/core/Grid';

import { Loading, Form, InputField } from 'components';

class Help extends PureComponent {
    constructor(props) {
        super(props);

        this.email = '';
    }
    
    getInputFieldText = (id) => {
        return document.getElementById(id).value;
    }

    requestResetPassword = (event) => {
        event.preventDefault();
        
        const newPassword = this.getInputFieldText('newPassword');
        const confirmPassword = this.getInputFieldText('confirmPassword');

        if(newPassword !== confirmPassword) {
            this.props.openDialog("비밀번호가 일치하지 않습니다.");
            return;
        }

        axios.post('/account/help/password/reset', { email: this.email, newPassword })
            .then(response => {
                this.props.openDialog(response.data.message, () => {
                    this.props.history.push('/');
                });
            })
            .catch(error => {
                this.props.openDialog(error.response.data.message);
            })
    }
   
    requestVerifyCode = (event) => {
        event.preventDefault();

        this.email = this.getInputFieldText('email');
        if(this.email === "") { 
            this.props.openDialog("이메일 주소를 입력해주세요.");
            return;
        }

        this.props.requestEmailVerifyCode(this.email, false)
            .then(result => this.props.openDialog(result))
            .catch(error => this.props.openDialog(error))
    }

    confirmVerifyCode = (event) => {
        event.preventDefault();   

        const verifyCode = this.getInputFieldText('verifyCode');

        this.props.confirmEmailVerifyCode(this.email, verifyCode)
            .catch(error => this.props.openDialog(error))
    } 

    componentWillUnmount() {
        this.props.expireVerifyCode();
    }
    
    render() {
        const { emailVerification } = this.props;

        if(emailVerification.waitResponse) {
            return <Loading size="large" color="white" spacing="200px"/>;
        }

        if(!emailVerification.isSentRequest) {
            return (
                <Form
                    title="비밀번호 재설정"
                    submitName="인증번호 요청"
                    onSubmit={this.requestVerifyCode}
                >  
                    <EmailInputField/>
                </Form>
            );
        }

        return (
            <Form
                title="비밀번호 재설정"
                submitName={emailVerification.isVerified ? '재설정하기' : '제출하기'}
                onSubmit={emailVerification.isVerified ? this.requestResetPassword : this.confirmVerifyCode}
            >
                { emailVerification.isVerified ? <PasswordInputField/> : <VerifyCodeInputField/> }
            </Form>
        );
    }
}

const EmailInputField = () => {
    return (
        <Grid container spacing={2}>
            <Grid item xs={12}>
                <InputField id="email" label="이메일 주소 입력"/>
            </Grid>
        </Grid>
    );
}

const VerifyCodeInputField = () => {
    return (
        <Grid container spacing={2}>
            <Grid item xs={12}>
                <InputField id="verifyCode" label="인증번호 입력"/>
            </Grid>
        </Grid>
    );
} 

const PasswordInputField = () => {
    return (
        <Grid container spacing={2}>
            <Grid item xs={12}>
                <InputField id="newPassword" type="password" label="새로운 비밀번호 입력" autoComplete="new-password" />
            </Grid>
            <Grid item xs={12}>
                <InputField id="confirmPassword" type="password" label="비밀번호 확인" />
            </Grid>
        </Grid>
    );    
}

const mapStateToProps = (state) => {
    return { 
        emailVerification: state.verification.get('email').toObject()
    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        requestEmailVerifyCode: (email, isNewEmail) => {
            return dispatch(requestEmailVerifyCode(email, isNewEmail));
        },
        confirmEmailVerifyCode: (email, verifyCode) => {
            return dispatch(confirmEmailVerifyCode(email, verifyCode));
        },
        expireVerifyCode: () => dispatch(expireVerifyCode()),
        openDialog: (message, callback) => { 
            return dispatch(openDialog({ message: message, callback: callback }));
        }
    }
}

export default connect(mapStateToProps, mapDispatchToProps)(Help);