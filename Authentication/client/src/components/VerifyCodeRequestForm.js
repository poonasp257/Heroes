import React, { PureComponent } from 'react';
import PropTypes from 'prop-types';

import { connect } from 'react-redux';
import { requestEmailVerifyCode } from 'modules/verification';
import { openDialog } from 'modules/dialog';

import Grid from '@material-ui/core/Grid';
import Form from './Form';
import InputField from './InputField';

class VerifyCodeRequestForm extends PureComponent {
    constructor(props) {
        super(props);

        this.openDialog = props.openDialog;
        this.requestEmailVerifyCode = props.requestEmailVerifyCode;
    }

    requestVerifyCode = (event) => {
        event.preventDefault();

        const emailAddress = document.getElementById('email').value;
        if (emailAddress === "") {
            this.openDialog("이메일 주소를 입력해주세요.");
            return;
        }

        this.requestEmailVerifyCode(emailAddress, false)
            .then(result => this.openDialog(result))
            .catch(error => this.openDialog(error))
    }

    render() {
        return (
            <Form
                name={this.props.name}
                submitName="인증번호 요청"
                onSubmit={this.requestVerifyCode}
            >
                <Grid container spacing={2}>
                    <Grid item xs={12}>
                        <InputField id="email" label="이메일 주소 입력" />
                    </Grid>
                </Grid>
            </Form>
        );
    }
}

VerifyCodeRequestForm.propTypes = {
    name: PropTypes.string.isRequired
}

const mapDispatchToProps = (dispatch) => {
    return {
        requestEmailVerifyCode: (email, isNewEmail) => {
            return dispatch(requestEmailVerifyCode(email, isNewEmail));
        },
        openDialog: (message, callback) => {
            return dispatch(openDialog({ message, callback }));
        }
    }
}

export default connect(null, mapDispatchToProps)(VerifyCodeRequestForm);