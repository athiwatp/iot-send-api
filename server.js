var express = require('express')
var bodyParser = require('body-parser')
var app = express()
var cors = require('cors')

app.use(cors())
app.use(bodyParser.json())

app.set('port', (process.env.PORT || 4000))
app.use(bodyParser.urlencoded({extended: false}))
app.use(bodyParser.json())


app.post('/api/temp', function (req, res) {
	console.log(req.query.temp)
	res.send('success : ' + req.query.temp)
})

app.listen(app.get('port'), function () {
  console.log('run at port', app.get('port'))
})