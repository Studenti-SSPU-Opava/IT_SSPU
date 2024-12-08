// Shape calculator logic
let shapeCalculator = {
    calcCircle: function (radius) {
      return Math.PI * radius * radius;
    },
    calcSquare: function (side) {
      return side * side;
    },
    calcTriangle: function (base, height) {
      return 0.5 * base * height;
    }
  };

  const shape = document.getElementById("shape");
  const circle = document.getElementById("circle");
  const rect1 = document.getElementById("rect1");
  const rect2 = document.getElementById("rect2");
  const radius = document.getElementById("radius");
  const side = document.getElementById("side");
  const base = document.getElementById("base");
  const height = document.getElementById("height");
  const result = document.getElementById("result");
  const calculate = document.getElementById("calculate");

  function updateInputs() {
    const selectedShape = shape.value;
  

    circle.classList.add("hidden");
    rect1.classList.add("hidden");
    rect2.classList.add("hidden");
  
    if (selectedShape === "circle") {
      circle.classList.remove("hidden");
    } else if (selectedShape === "square") {
      rect1.classList.remove("hidden");
    } else if (selectedShape === "triangle") {
      rect2.classList.remove("hidden");
    }
  }
  
  calculate.addEventListener("click", function () {
    const selectedShape = shape.value;
    let calcResult = "";
  
    if (selectedShape === "circle") {
      const r = parseFloat(radius.value);
      if (!isNaN(r)) {
        calcResult = `Circle Area: ${shapeCalculator.calcCircle(r).toFixed(2)}`;
      } else {
        calcResult = "Please enter a valid radius.";
      }
    } else if (selectedShape === "square") {
      const s = parseFloat(side.value);
      if (!isNaN(s)) {
        calcResult = `Square Area: ${shapeCalculator.calcSquare(s).toFixed(2)}`;
      } else {
        calcResult = "Please enter a valid side length.";
      }
    } else if (selectedShape === "triangle") {
      const b = parseFloat(base.value);
      const h = parseFloat(height.value);
      if (!isNaN(b) && !isNaN(h)) {
        calcResult = `Triangle Area: ${shapeCalculator.calcTriangle(b, h).toFixed(2)}`;
      } else {
        calcResult = "Please enter valid base and height values.";
      }
    }
  
    result.innerHTML = calcResult;
  });
  
  shape.addEventListener("change", updateInputs);
  