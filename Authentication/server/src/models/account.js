import mongoose from 'mongoose';
import autoIncrement from 'mongoose-auto-increment';
import bcrypt from 'bcryptjs';

var connection = mongoose.createConnection('mongodb://127.0.0.1/heroes', { 
    useNewUrlParser: true, 
    useUnifiedTopology: true,
    useFindAndModify: false,
    useCreateIndex: true 
});

autoIncrement.initialize(connection);

const Schema = mongoose.Schema;

const Account = new Schema({
    email: String,
    username: String,
    password: String,
    created: { type: Date, default: Date.now }    
});

Account.plugin(autoIncrement.plugin, 'account');

Account.methods.generateHash = function(password) {
    const salt = bcrypt.genSaltSync(8);
    return bcrypt.hashSync(password, salt);
};

Account.methods.validateHash = function(password) {
    return bcrypt.compareSync(password, this.password);
};

export default mongoose.model('account', Account);