import React, { PureComponent } from 'react';
import axios from 'axios';

import { connect } from 'react-redux';
import { requestEmailVerifyCode, requestConfirmEmailVerifyCode, expireVerifyCode } from 'modules/verification';
import { openDialog } from 'modules/dialog';

import Grid from '@material-ui/core/Grid';

import { Loading, Form, InputField, VerificationButton } from 'components';

class SignUp extends PureComponent {
    getInputFieldText = (id) => {
        return document.getElementById(id).value;
    }

    handleSubmit = (event) => {
        event.preventDefault();
        if(!this.props.emailVerification.isVerified) {
            this.props.openDialog("이메일 인증이 필요합니다.");
            return; 
        }
        
        const email = this.getInputFieldText('email');
        const username =  this.getInputFieldText('username');
        const password =  this.getInputFieldText('password');
        axios.post('/account/signup', { email, username, password })
            .then(response => {
                this.props.openDialog(response.data.message, () => {
                    this.props.history.push('/');
                });
            })
            .catch(error => this.props.openDialog(error.response.data.message));
    }
    
    requestVerifyCode = (event) => {
        event.preventDefault();

        const email = this.getInputFieldText('email');
        if(email === "") { 
            this.props.openDialog("이메일 주소를 입력해주세요.");
            return;
        }

        this.props.requestEmailVerifyCode(email, true)
            .then(result => this.props.openDialog(result))
            .catch(error => this.props.openDialog(error))
    }

    confirmVerifyCode = (event) => {
        event.preventDefault();   

        const email = this.getInputFieldText('email');
        const verifyCode = this.getInputFieldText('verifyCode');
        this.props.requestConfirmEmailVerifyCode(email, verifyCode)
            .then(result => this.props.openDialog(result))
            .catch(error => this.props.openDialog(error))
    } 

    componentWillUnmount() {
        this.props.expireVerifyCode();
    }

    render() {
        const { emailVerification } = this.props;

        return (
            <Form
                name="회원가입"
                submitName="가입하기"
                onSubmit={this.handleSubmit}
            >
                <Grid container spacing={2} alignItems="center">
                    <Grid item xs={12}>
                        <InputField 
                            id="email" 
                            label="이메일 주소 입력" 
                            autoComplete="email"
                            disabled={emailVerification.isSentRequest || emailVerification.isVerified}
                        />
                    </Grid>
                    <Grid item xs={8}>                        
                        <InputField 
                            id="verifyCode" 
                            label="인증번호 입력" 
                            autoComplete="off"
                            disabled={emailVerification.isVerified}
                        />
                    </Grid>
                    <Grid item xs={4}>
                        {emailVerification.waitResponse ? ( 
                            <Loading size="small" color="#5AAEF6"/>
                        ) : (
                            <VerificationButton 
                                fontColor="white" 
                                color="#5AAEF6" 
                                size="large" 
                                text={emailVerification.isSentRequest ? '확인' : '인증 요청'}
                                onClick={emailVerification.isSentRequest ? this.confirmVerifyCode : this.requestVerifyCode}
                                checked={emailVerification.isVerified}
                            />
                        )}
                    </Grid>
                    <Grid item xs={12}>                        
                        <InputField id="username" label="아이디 입력" autoComplete="username"/>
                    </Grid>
                    <Grid item xs={12}>
                        <InputField id="password" type="password" label="비밀번호 입력" autoComplete="current-password"/>
                    </Grid>
                </Grid>
            </Form>
        );
    }
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
        requestConfirmEmailVerifyCode: (email, verifyCode) => {
            return dispatch(requestConfirmEmailVerifyCode(email, verifyCode));
        },
        expireVerifyCode: () => dispatch(expireVerifyCode()),
        openDialog: (message, callback) => { 
            return dispatch(openDialog({ message: message, callback: callback }));
        }
    }
}

export default connect(mapStateToProps, mapDispatchToProps)(SignUp);