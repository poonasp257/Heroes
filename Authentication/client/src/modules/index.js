import { combineReducers } from 'redux';

import dialog from './dialog';
import verification from './verification';

export default combineReducers({
    dialog, verification
});