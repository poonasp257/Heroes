import { createAction, handleActions } from 'redux-actions';
import { Map } from 'immutable';

const DIALOG_OPEN = 'dialog/OPEN';
const DIALOG_CLOSE = 'dialog/CLOSE';

export const openDialog = createAction(DIALOG_OPEN); // message, (options: callback)
export const closeDialog = createAction(DIALOG_CLOSE);

const initialState = Map({    
    isOpened: false,
    message: '',
    callback: null
});

export default handleActions({
    [DIALOG_OPEN]: (state, action) => {
        const { message, callback } = action.payload;       

        return state.set('isOpened', true)
                    .set('message', message)
                    .set('callback', callback)
    },
    [DIALOG_CLOSE]: state => {
        return state.set('isOpened', false)
    }
}, initialState);