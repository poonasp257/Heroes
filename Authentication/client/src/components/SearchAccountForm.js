import React, { PureComponent } from 'react';
import PropTypes from 'prop-types';
import styled from 'styled-components';

import { connect } from 'react-redux';
import { requestSearchAccount } from 'modules/verification';
import { openDialog } from 'modules/dialog';

import Grid from '@material-ui/core/Grid';
import Form from './Form';
import VerifyCodeConfirmForm from './VerifyCodeConfirmForm';

class SearchAccountForm extends PureComponent {
    constructor(props) {
        super(props);

        this.username = null;
    }

    searchAccount = (emailAddress, verifyCode) => {
        this.props.requestSearchAccount(emailAddress, verifyCode)
            .then(result => {
                const { error, username } = result;
                if(error) { 
                    this.props.openDialog(error);
                    return;
                }

                this.username = username;
            })
            .catch(error => this.props.openDialog(error))
    }

    render() {
        if (!this.props.isVerified) {
            return (
                <VerifyCodeConfirmForm 
                    confirm={this.searchAccount}
                    name={this.props.name}
                />
            );
        }

        return (
            <Form name={this.props.name}>
                <Grid container spacing={3}>
                    <Grid item xs={12}>
                        현재 <b>{this.props.emailAddress}</b>은 <br/>
                        다음 계정과 연결되어 있습니다.
                    </Grid>
                    <Grid item xs={12}>
                        <UserName>
                            "{this.props.username}"
                        </UserName>
                    </Grid>
                </Grid>
            </Form>
        );
    }
}

SearchAccountForm.propTypes = {
    name: PropTypes.string.isRequired
}

const UserName = styled.span` 
    font-size: 18px;
    font-weight: bold;
`;

const mapStateToProps = (state) => {
    return {
        isVerified: state.verification.getIn(['email', 'isVerified']),
        emailAddress: state.verification.getIn(['email', 'address']),
        username: state.verification.getIn(['email', 'username'])
    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        requestSearchAccount: (email, verifyCode) => { 
            return dispatch(requestSearchAccount(email, verifyCode));
        },
        openDialog: (message, callback) => { 
            return dispatch(openDialog({ message, callback }));
        }
    }
}

export default connect(mapStateToProps, mapDispatchToProps)(SearchAccountForm);