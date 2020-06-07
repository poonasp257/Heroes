import React, { PureComponent } from 'react';
import PropTypes from 'prop-types';

import { connect } from 'react-redux';
import { requestConfirmEmailVerifyCode, requestResetPassword } from 'modules/verification';
import { openDialog } from 'modules/dialog';

import Grid from '@material-ui/core/Grid';
import Form from './Form';
import InputField from './InputField';
import VerifyCodeConfirmForm from './VerifyCodeConfirmForm';

class PasswordResetForm extends PureComponent {   
    constructor(props) {
        super(props);

        this.emailAddress = props.emailAddress;
        this.openDialog = props.openDialog;
        this.requestResetPassword = props.requestResetPassword;
    }

    resetPassword = (event) => {
        event.preventDefault();
        
        const newPassword = document.getElementById('newPassword').value;
        const confirmPassword = document.getElementById('confirmPassword').value;
        if(newPassword !== confirmPassword) {
            this.openDialog("비밀번호가 일치하지 않습니다.");
            return;
        }

        this.requestResetPassword(this.emailAddress, newPassword)
            .then(result => this.openDialog(result, () => this.props.history.push('/')))
            .catch(error => this.openDialog(error))
    }

    render() {
        if (!this.props.isVerified) {
            return (
                <VerifyCodeConfirmForm 
                    name={this.props.name}
                    confirm={this.props.requestConfirmEmailVerifyCode}
                />
            );
        }

        return (
            <Form
                name={this.props.name}
                submitName='재설정하기'
                onSubmit={this.resetPassword}
            >
                <Grid container spacing={2}>
                    <Grid item xs={12}>
                        <InputField 
                            id="newPassword" 
                            type="password" 
                            label="새로운 비밀번호 입력" 
                            autoComplete="new-password" 
                        />
                    </Grid>
                    <Grid item xs={12}>
                        <InputField 
                            id="confirmPassword" 
                            type="password" 
                            label="비밀번호 확인" 
                        />
                    </Grid>
                </Grid>
            </Form>
        );
    }
}

PasswordResetForm.propTypes = {
    name: PropTypes.string.isRequired
}

const mapStateToProps = (state) => {
    return {
        isVerified: state.verification.getIn(['email', 'isVerified']),
        emailAddress: state.verification.getIn(['email', 'address'])
    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        requestConfirmEmailVerifyCode: (email, verifyCode) => {
            return dispatch(requestConfirmEmailVerifyCode(email, verifyCode));
        },
        requestResetPassword: (email, password) => { 
            return dispatch(requestResetPassword(email, password));
        },
        openDialog: (message, callback) => { 
            return dispatch(openDialog({ message, callback }));
        }
    }
}

export default connect(mapStateToProps, mapDispatchToProps)(PasswordResetForm);