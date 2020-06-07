import express from 'express';
import mongoose from 'mongoose';
import account from './routes/account';
import cors from 'cors';

const app = express();
const clientIP = process.env.CLIENT_IP;
const clientPort = process.env.CLIENT_PORT;
const serverPort = process.env.SERVER_PORT;

const corsOptions = { 
    origin: `${clientIP}:${clientPort}`, 
    credentials: true
};
app.use(cors(corsOptions));

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

app.use('/account', account);

app.listen(serverPort, () => console.log("Login Server listening on port " + serverPort));    