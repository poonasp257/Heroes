import express from 'express';
import session from 'express-session';
import mongoose from 'mongoose';
import account from './routes/account';

const app = express();
const port = 9100;

app.use(express.urlencoded({ extended: false }))
app.use(express.json());

const db = mongoose.connection;
db.on('error', console.error);
db.once('open', () => console.log('Connected to mongodb server'));

mongoose.connect('mongodb://127.0.0.1/heroes', { 
    useNewUrlParser: true, 
    useUnifiedTopology: true,
    useFindAndModify: false 
});

app.use(session({
    secret: '#@!#DSFWErHeroesFDG#$',
    resave: false,
    saveUninitialized: true
}));

app.use('/account', account);

app.listen(port, () => console.log("Login Server listening on port 9100"));    