import React from 'react';
import PropTypes from 'prop-types';

import TextField from '@material-ui/core/TextField';

export default function InputField({ id, type, label, ...props }) {
    return (
        <TextField
            variant="outlined"
            required
            fullWidth
            name={id}
            label={label}
            type={type}
            id={id}
            {...props}
        />
    );
}

InputField.propTypes = {
    id: PropTypes.string.isRequired,
    label: PropTypes.string.isRequired,
    type: PropTypes.string,
};