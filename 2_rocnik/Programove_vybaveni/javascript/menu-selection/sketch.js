const menuItems = ["lines", "random line", "chessboard"];
let currentMode = "menu";

function setup() {
  createCanvas(600, 600);
}

function draw() {
  background(220);

  switch (currentMode) {
    case "lines":
      drawLines();
      break;
    case "random line":
      drawRandomLine();
      break;
    case "chessboard":
      drawChessboard();
      break;
    default:
      drawMenu();
  }
}

function keyPressed() {
  if (key === "1") {
    currentMode = "lines";
  } else if (key === "2") {
    currentMode = "random line";
  } else if (key === "3") {
    currentMode = "chessboard";
  } else if (key === " " || keyCode === 32) {
    currentMode = "menu";
  }
}

function drawMenu() {
  stroke(128);
  strokeWeight(5);
  fill(150, 100, 200, 100);
  rect(20, 20, 250, 200, 20);

  fill(0);
  stroke(0);
  strokeWeight(0);
  textSize(15);
  text("Menu - select effect", 40, 50);

  strokeWeight(1);
  line(40, 60, 170, 60);

  strokeWeight(0);
  for (let i = 0; i < menuItems.length; i++) {
    text(`${i + 1} - ${menuItems[i]}`, 40, 80 + i * 20);
  }
}

function drawLines() {
  background(255);
  let x = 0;
  let index = 0;

  while (x < width) {
    let lineWeight = random(5, 10);
    strokeWeight(lineWeight);
    stroke(index % 2 === 0 ? "black" : "white");
    line(x, 0, x + lineWeight, height);
    x += lineWeight;
    index++;
  }
}

function drawRandomLine() {
  background(255);

  let x = random(width);
  let y = random(height);
  let lineLength = 150;

  stroke("black");
  strokeWeight(5);
  line(x, y, x + lineLength, y + lineLength);
}

function drawChessboard() {
  background(255);

  let tileSize = 75;

  for (let y = 0; y < height; y += tileSize) {
    for (let x = 0; x < width; x += tileSize) {
      let col = x / tileSize;
      let row = y / tileSize;

      if ((col + row) % 2 === 0) {
        fill("black");
      } else {
        fill("white");
      }

      stroke("black");
      strokeWeight(1);
      rect(x, y, tileSize, tileSize);
    }
  }
}
