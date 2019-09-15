import express from 'express';
import session from 'express-session';
import morgan from 'morgan';
import bodyParser from 'body-parser';
import mongoose from 'mongoose';

const app = express();
const port = 5000;

app.use(morgan('dev'));
app.use(bodyParser.json());

const db = mongoose.connection;
db.on('error', console.error);
db.once('open', () => console.log("Connected to mongodb server"));
mongoose.connect('mongodb://localhost/heroes', { useNewUrlParser: true });

app.use(session({
    secret: '3dfg#23kdsf@heroes@#!G?',
    resave: false,
    saveUninitialized: true
}));

app.post('/signup', (req, res) => {

});

app.post('signin', (req, res) => {

});

router.get('/getinfo', (req, res) =>{
});

router.post('/logout', (req, res) => {
});

app.listen(port);

app.use((err, req, res) => {
    console.error(err.stack);
    res.status(500).send('Something broke!');
});