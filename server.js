var SerialPort = require("serialport").SerialPort
var serialPortButtons = new SerialPort("/dev/ttyACM2", {
    baudrate: 9600,
    dataBits: 8, 
    parity: 'none', 
    stopBits: 1, 
    flowControl: false 
});
var serialPortCube = new SerialPort("/dev/ttyACM3", {
    baudrate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false
});
var serialPortPlayer1 = new SerialPort("/dev/ttyACM4", {
    baudrate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false
});

var serialPortPlayer2 = new SerialPort("/dev/ttyACM5", {
    baudrate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false
});

var led_value = 0;
var led_value = 0;
var score_player1 = 1;
var score_player2 = 1;
var blinkstate = 0;
var won = 0;

serialPortButtons.on("open", function(){
    console.log('loaded buttons');
    setTimeout(mainLoop, 3000);
});

serialPortCube.on('open', function(){
    console.log('loaded cube');
});

serialPortPlayer1.on('open', function(){
    console.log('loaded player 1');
});

serialPortPlayer2.on('open', function(){
    console.log('loaded player 2');
});

function mainLoop() {
  console.log('open');

  serialPortPlayer1.write(""+score_player1);
  serialPortPlayer2.write(""+score_player2);

  start_led_countdown();

  serialPortButtons.on('data', function(data) { 
    receivedData = data.toString();
    // console.log(receivedData);
    
    if(score_player1>6){
        reset();
        return;
    }

    if(score_player2>6){
        reset();
        return;
    }

    if(led_value == 1){
        led_off();
        start_led_countdown();
        if(receivedData == "1"){
            score_player1 += 1;
        } else {
            score_player2 += 1;
        }
    } else {
        if(receivedData == "1"){
            if(score_player1>1){
                score_player1 -= 1;
            }
        } else {
            if(score_player2>1){
                score_player2 -= 1;
            }
        }
        console.log('CHEATER!');
    }

    console.log("Score player 1: ", score_player1); 
    console.log("Score player 2: ", score_player2); 
    serialPortPlayer1.write(""+score_player1);
    serialPortPlayer2.write(""+score_player2);
    if(score_player1>6){
        won = 1;
        blink_leds1()
        return;
    }

    if(score_player2>6){
        won = 1;
        blink_leds2()
        return;
    }

  });
}

function blink_leds1(){
    if(blinkstate == 0){
        serialPortPlayer1.write(""+blinkstate);
    } else {
        serialPortPlayer1.write(""+7);
    }
    blinkstate = (blinkstate + 1) % 2
    if(won==1){
        setTimeout(blink_leds1, 500);
    }
}

function blink_leds2(){
    if(blinkstate == 0){
        serialPortPlayer2.write(""+blinkstate);
    } else {
        serialPortPlayer2.write(""+7);
    }
    blinkstate = (blinkstate + 1) % 2
    if(won==1){
        setTimeout(blink_leds2, 500);
    }
}

function led_off(){
    console.log('led off');
    // serialPortButtons.write("0E");
    serialPortCube.write("x");
    led_value = 0;
}

function led_on(){
    console.log('led on');
    // serialPortButtons.write("1E");
    serialPortCube.write("z");
    led_value = 1;
}

function start_led_countdown(){
    var min_milliseconds = 2000,
        max_milliseconds = 7000,
        milliseconds = Math.random()*(max_milliseconds - min_milliseconds) + min_milliseconds;
    setTimeout(led_on, milliseconds);
}

function reset(){
    won = 0;
    serialPortPlayer1.write(""+1);
    serialPortPlayer2.write(""+1);
    score_player1=1;
    score_player2=1;
    start_led_countdown();
}
