import React, { PureComponent } from 'react';
import { connect } from 'react-redux';

import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogContentText from '@material-ui/core/DialogContentText';
import DialogTitle from '@material-ui/core/DialogTitle';
import Button from '@material-ui/core/Button';

import { closeDialog } from 'modules/dialog';

class AlertBox extends PureComponent {
    handleClose = () => {
        if(this.props.callback) {
            this.props.callback();
        }
        this.props.closeDialog();
    }

    render() {
        return (
            <Dialog
                onClose={this.handleClose}
                open={this.props.isOpened}
            >
                <DialogTitle>Heroes</DialogTitle>
                <DialogContent>
                    <DialogContentText>
                        {this.props.message}
                    </DialogContentText>
                </DialogContent>
                <DialogActions>
                    <Button onClick={this.handleClose} color="primary">
                        확인
                    </Button>
                </DialogActions>
            </Dialog>
        );
    }
}

const mapStateToProps = (state) => {
    return state.dialog.toObject();
}

const mapDispatchToProps = (dispatch) => {
    return { closeDialog: () => dispatch(closeDialog()) }
}

export default connect(mapStateToProps, mapDispatchToProps)(AlertBox);