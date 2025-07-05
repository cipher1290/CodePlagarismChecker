const express = require('express');
const cors = require('cors');
const app = express();
const analyzeRoute = require('./routes/analyzeRoutes');

// MiddleWares
app.use(cors());
app.use(express.json());

// Routes
app.use('/api', analyzeRoute);

PORT = 5000;
//test route
app.get('/', (req, res) => {
    console.log('Inside homepage...');
    res.send('Hi!!! its me...');
})

app.listen(PORT, () => {
    console.log('Application is running...');
})