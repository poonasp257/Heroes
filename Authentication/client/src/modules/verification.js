import { createAction, handleActions } from 'redux-actions';
import { Map } from 'immutable';
import axios from 'axios';

const EMAIL_VERIFYCODE_REQUEST = 'verification/EMAIL_VERIFYCODE_REQUEST';
const EMAIL_VERIFYCODE_RECEIVED = 'verification/EMAIL_VERIFYCODE_RECEIVED';
const EMAIL_VERIFYCODE_CONFIRM = 'verification/EMAIL_VERIFYCODE_CONFIRM';
const EMAIL_VERIFYCODE_CONFIRM_SUCCESS = 'verification/EMAIL_VERIFYCODE_CONFIRM_SUCCESS';
const EMAIL_VERIFYCODE_CONFIRM_FAILED = 'verification/EMAIL_VERIFYCODE_CONFIRM_FAILED';
const EMAIL_VERIFYCODE_EXPIRED = 'verification/EMAIL_VERIFYCODE_EXPIRED';

export function requestEmailVerifyCode(email, isNewEmail) {
    return (dispatch) => {
        dispatch({ type: EMAIL_VERIFYCODE_REQUEST});

        return axios.post('/account/email/verify/request', { email, isNewEmail })
            .then(response => {
                dispatch({ type: EMAIL_VERIFYCODE_RECEIVED });
                return response.data.message;
            })
            .catch(error => {       
                dispatch({ type: EMAIL_VERIFYCODE_EXPIRED });     
                if(error) throw error.response.data.message;
            })
    }    
}

export function confirmEmailVerifyCode(email, verifyCode) {
    return (dispatch) => {
        dispatch({ type: EMAIL_VERIFYCODE_CONFIRM });

        return axios.post('/account/email/verify/confirm', { email, verifyCode })
            .then(response => {
                dispatch({ type: EMAIL_VERIFYCODE_CONFIRM_SUCCESS });
                return response.data.message;
            })
            .catch(error => {           
                dispatch({ type: EMAIL_VERIFYCODE_CONFIRM_FAILED });
                if(error) throw error.response.data.message;  
            })
    }    
}

export const expireVerifyCode = createAction(EMAIL_VERIFYCODE_EXPIRED);

const initialState = Map({ 
    email: Map({
        isVerified: false, 
        isSentRequest: false,
        waitResponse: false
    })
});

export default handleActions({
    [EMAIL_VERIFYCODE_REQUEST]: state => {
        return state.setIn(['email', 'isSentRequest'], true)
                    .setIn(['email', 'waitResponse'], true)
    },
    [EMAIL_VERIFYCODE_RECEIVED]: state => {
        return state.setIn(['email', 'waitResponse'], false)                    
    },
    [EMAIL_VERIFYCODE_CONFIRM]: state => {
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
        return state.setIn(['email', 'isSentRequest'], false)
                    .setIn(['email', 'waitResponse'], false)
                    .setIn(['email', 'isVerified'], false)
    }
}, initialState);