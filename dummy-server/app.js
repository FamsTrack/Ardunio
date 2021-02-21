const express = require('express')
const app = express()
const cors = require('cors')
const port = 3000
const {Arduino} = require('./models')

app.use(express.json())
app.use(express.urlencoded({extended: true}))
app.use(cors())

app.get('/', (req,res)=>{
    res.status(200).send("arduino server")
})
app.get('/update/:arduino_unique_key', async (req,res)=>{
    try {
        // console.log(req.params,'............', req.query);
        const {arduino_unique_key} = req.params
        const data = req.query
        const result = await Arduino.update(data,{
            where:{
                arduino_unique_key
            },
            returning: true
        })
        const {buzzer} = result[1][0]
        res.status(200).send(buzzer?'1':'0')
    } catch (error) {
        console.log(error);
    }
})

app.listen(port,()=>{
    console.log('dummy server running at',port);
})