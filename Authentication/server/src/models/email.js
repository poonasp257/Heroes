import mongoose from 'mongoose';

const Schema = mongoose.Schema;

const Email = new Schema({
    email: { type: String, required: true },
    isVerified: { type: Boolean, default: false },
    verifyCode: { type: String, required: true },
    created: { type: Date, default: Date.now }
});

export default mongoose.model('email', Email);