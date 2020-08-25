
"use strict";

var panelconf = {
    panel_wh: 0, // なんでもいいが、原則0。
    panel_wh_split: 11.0, // 必ず奇数。
};

var canvas, cr;
var player = {x:0, y:0};

function open_map_process(){
    var rawFile = new XMLHttpRequest();
    rawFile.open("GET", "https://raw.githubusercontent.com/Perukii/mulpsi/master/README.md?token=ANYTTYOQ3WJ2VPTFSZKDZ4C7ITS7S", true);
    rawFile.onreadystatechange = function ()
    {
        if(rawFile.readyState === 4)
        {
            if(rawFile.status === 200)
            {
                var allText = rawFile.responseText;
                alert(allText);
            }
        }

    }
    rawFile.onerror = function() {
        alert("Request failed");
    };
    rawFile.send(null);
}

function read_map_process(){

}

function draw_process(){

    cr.fillStyle = "white";
    cr.fillRect(0,0,canvas.width,canvas.height);

    cr.fillStyle = "black";

    cr.fillRect(
        panelconf.panel_wh*(panelconf.panel_wh_split-1)/2.0,
        panelconf.panel_wh*(panelconf.panel_wh_split-1)/2.0,
        panelconf.panel_wh,
        panelconf.panel_wh
    );

    cr.fillStyle = "orange";
    
    cr.fillRect(
        panelconf.panel_wh*player.x,
        panelconf.panel_wh*player.y,
        panelconf.panel_wh,
        panelconf.panel_wh
    );
}

function key_process(event){
    switch(event.keyCode){
        case 37: player.x--;break;
        case 38: player.y--;break;
        case 39: player.x++;break;
        case 40: player.y++;break;
    }
    draw_process();
}

function main(){
    open_map_process();

    canvas = document.getElementById("canvas");
    cr     = canvas.getContext("2d");
    onkeydown = key_process;
    panelconf.panel_wh = canvas.width/panelconf.panel_wh_split;
    draw_process();

}