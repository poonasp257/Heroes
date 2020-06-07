import React, { PureComponent } from 'react';

import { connect } from 'react-redux';
import { expireVerifyCode } from 'modules/verification';

import { 
    Loading, 
    VerifyCodeRequestForm,
    SearchAccountForm,
    PasswordResetForm
} from 'components';

class Help extends PureComponent {
    constructor(props) {
        super(props);

        const pathName = props.history.location.pathname;
        const splitedPathName = pathName.split('/');

        this.title = props.title;
        this.page = splitedPathName[splitedPathName.length - 1];
    }

    componentWillUnmount() {
        this.props.expireVerifyCode();
    }
    
    render() {
        const { waitResponse, isSentRequest } = this.props.emailVerification;
        if(waitResponse) return <Loading size="large" color="white" spacing="200px"/>;
        else if(!isSentRequest) return <VerifyCodeRequestForm name={this.title}/>;
        
        switch (this.page) {
            case 'account':
                return <SearchAccountForm name={this.title}/>;
            case 'password':
                return <PasswordResetForm name={this.title}/>;
            default:
                return null;
        }
    }
}

const mapStateToProps = (state) => {
    return { 
        emailVerification: state.verification.get('email').toObject()
    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        expireVerifyCode: () => dispatch(expireVerifyCode())
    }
}

export default connect(mapStateToProps, mapDispatchToProps)(Help);