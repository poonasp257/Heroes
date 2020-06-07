import { createAction, handleActions } from 'redux-actions';
import { Map } from 'immutable';
import axios from 'axios';

const EMAIL_VERIFYCODE_REQUEST = 'verification/EMAIL_VERIFYCODE_REQUEST';
const EMAIL_VERIFYCODE_RECEIVED = 'verification/EMAIL_VERIFYCODE_RECEIVED';

const EMAIL_VERIFYCODE_CONFIRM_REQUEST = 'verification/EMAIL_VERIFYCODE_CONFIRM_REQUEST';
const EMAIL_VERIFYCODE_CONFIRM_SUCCESS = 'verification/EMAIL_VERIFYCODE_CONFIRM_SUCCESS';
const EMAIL_VERIFYCODE_CONFIRM_FAILED = 'verification/EMAIL_VERIFYCODE_CONFIRM_FAILED';
const EMAIL_VERIFYCODE_EXPIRED = 'verification/EMAIL_VERIFYCODE_EXPIRED';

const SEARCH_ACCOUNT_REQUEST = 'verification/SEARCH_ACCOUNT_REQUEST';
const SEARCH_ACCOUNT_SUCCESS = 'verification/SEARCH_ACCOUNT_SUCCESS';
const SEARCH_ACCOUNT_FAIELD = 'verification/SEARCH_ACCOUNT_FAIELD';

const WAIT_FOR_RESPONSE = 'verification/WAIT_FOR_RESPONSE';
const RECEIVED_RESPONSE = 'verification/RECEIVED_RESPONSE';

axios.defaults.baseURL = process.env.REACT_APP_AUTH_SERVER_IP;

export function requestEmailVerifyCode(email, isNewEmail) {
    return (dispatch) => {
        dispatch({
            address: email,
            type: EMAIL_VERIFYCODE_REQUEST
        });
        
        return axios.post('/account/email/verify/request', { email, isNewEmail })
            .then(response => {
                const { error, message } = response.data;
                if(error) {
                    dispatch({ type: EMAIL_VERIFYCODE_EXPIRED });
                    return error;
                }

                dispatch({ type: EMAIL_VERIFYCODE_RECEIVED });
                return message;
            })
            .catch(error => {   
                dispatch({ type: EMAIL_VERIFYCODE_EXPIRED });   
                if(error) throw error.response.data.message;
            })
    }    
}

export function requestConfirmEmailVerifyCode(email, verifyCode) {
    return (dispatch) => {
        dispatch({ type: EMAIL_VERIFYCODE_CONFIRM_REQUEST });

        return axios.post('/account/email/verify/confirm', { email, verifyCode })
            .then(response => {
                const { error, message } = response.data;
                if(error) {
                    dispatch({ type: EMAIL_VERIFYCODE_CONFIRM_FAILED });
                    return error;
                }

                dispatch({ type: EMAIL_VERIFYCODE_CONFIRM_SUCCESS });
                return message;
            })
            .catch(error => {           
                dispatch({ type: EMAIL_VERIFYCODE_CONFIRM_FAILED });
                if(error) throw error.response.data.message;  
            })
    }    
}

export function requestSearchAccount(email, verifyCode) {
    return (dispatch) => {
        dispatch({ type: SEARCH_ACCOUNT_REQUEST });

        return axios.post('/account/help/account/search', { email, verifyCode })
            .then(response => {        
                if(response.data.error) {
                    dispatch({ type: SEARCH_ACCOUNT_FAIELD });
                    return response.data;
                }
                
                dispatch({ 
                    username: response.data.username,
                    type: SEARCH_ACCOUNT_SUCCESS 
                });
                return response.data;
            })
            .catch(error => { 
                dispatch({ type: RECEIVED_RESPONSE });
                if(error) throw error.response.data.message;
            })
    }
}

export function requestResetPassword(email, newPassword) {
    console.log(email);
    return (dispatch) => {
        dispatch({ type: WAIT_FOR_RESPONSE });

        return axios.post('/account/help/password/reset', { email, newPassword })
            .then(response => {        
                dispatch({ type: RECEIVED_RESPONSE });

                const { error, message } = response.data;
                if(error) return error;

                return message;
            })
            .catch(error => { 
                dispatch({ type: RECEIVED_RESPONSE });
                if(error) throw error.response.data.message;
            })
    }
}

export const expireVerifyCode = createAction(EMAIL_VERIFYCODE_EXPIRED);

const initialState = Map({ 
    email: Map({
        username: null,
        address: null,
        isVerified: false, 
        isSentRequest: false,
        waitResponse: false
    })
});

export default handleActions({
    [WAIT_FOR_RESPONSE]: state => {
        return state.setIn(['email', 'waitResponse'], true)
    },
    [RECEIVED_RESPONSE]: state => {
        return state.setIn(['email', 'waitResponse'], false)
    },
    [EMAIL_VERIFYCODE_REQUEST]: (state, action) => {
        return state.setIn(['email', 'address'], action.address)
                    .setIn(['email', 'isSentRequest'], true)
                    .setIn(['email', 'waitResponse'], true)
    },
    [EMAIL_VERIFYCODE_RECEIVED]: state => {
        return state.setIn(['email', 'waitResponse'], false)                    
    },
    [EMAIL_VERIFYCODE_CONFIRM_REQUEST]: state => {
        return state.setIn(['email', 'waitResponse'], true)
    },
    [EMAIL_VERIFYCODE_CONFIRM_SUCCESS]: state => {
        return state.setIn(['email', 'isVerified'], true)
                    .setIn(['email', 'waitResponse'], false)
    },
    [EMAIL_VERIFYCODE_CONFIRM_FAILED]: state => {
        return state.setIn(['email', 'waitResponse'], false)
    },
    [EMAIL_VERIFYCODE_EXPIRED]: state => {
        return state.setIn(['email', 'address'], null)
                    .setIn(['email', 'isSentRequest'], false)
                    .setIn(['email', 'waitResponse'], false)
                    .setIn(['email', 'isVerified'], false)
    },
    [SEARCH_ACCOUNT_REQUEST]: state => {
        return state.setIn(['email', 'waitResponse'], true)
    },
    [SEARCH_ACCOUNT_SUCCESS]: (state, action) => {
        return state.setIn(['email', 'waitResponse'], false)
                    .setIn(['email', 'isVerified'], true)
                    .setIn(['email', 'username'], action.username)
    },
    [SEARCH_ACCOUNT_FAIELD]: state => {
        return state.setIn(['email', 'waitResponse'], false)
    }
}, initialState);