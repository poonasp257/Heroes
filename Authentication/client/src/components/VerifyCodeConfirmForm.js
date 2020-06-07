import React, { PureComponent } from 'react';
import PropTypes from 'prop-types';

import { connect } from 'react-redux';
import { openDialog } from 'modules/dialog';

import Grid from '@material-ui/core/Grid';
import Form from './Form';
import InputField from './InputField';

class VerifyCodeConfirmForm extends PureComponent {
    constructor(props) {
        super(props);

        this.emailAddress = props.emailAddress;
        this.openDialog = props.openDialog;
    }

    confirmVerifyCode = (event) => {    
        event.preventDefault();

        const verifyCode = document.getElementById('verifyCode').value;
        const promise = this.props.confirm(this.emailAddress, verifyCode)
        if(!promise) return;

        promise.then(result => {
                    if (result) this.openDialog(result);
                })
                .catch(error => this.openDialog(error))
    }

    render() {
        return (
            <Form
                name={this.props.name}
                submitName="제출하기"
                onSubmit={this.confirmVerifyCode}
            >
                <Grid container spacing={2}>
                    <Grid item xs={12}>
                        <InputField id="verifyCode" label="인증번호 입력" />
                    </Grid>
                </Grid>
            </Form>
        );
    }
}

VerifyCodeConfirmForm.propTypes = {
    name: PropTypes.string.isRequired,
    confirm: PropTypes.func
}

const mapStateToProps = (state) => {
    return {
        emailAddress: state.verification.getIn(['email', 'address'])
    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        openDialog: (message, callback) => {
            return dispatch(openDialog({ message, callback }));
        }
    }
}

export default connect(mapStateToProps, mapDispatchToProps)(VerifyCodeConfirmForm);