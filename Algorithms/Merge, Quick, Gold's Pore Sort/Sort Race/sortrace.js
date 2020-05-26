// sortrace.js
// This file implement race competition of three difference algorithms.
// It contains setup, draw, Mergesort, Gold's poresort, quicksort.
// Pick an array randomly from sample inputs and sort them using visualization.

//Sample Inputs
var myarray = [
  "05A627B2B603",
  "0656671040BA",
  "0684B8935754",
  "079A21834B65",
  "094878622616",
  "1AB347905286",
  "286103427859",
  "30530476510BA9",
  "328476510BA9",
  "3427561890BA",
  "41B382621985",
  "46379015B8A2",
  "5351A33A99BB",
  "593479088A15",
  "59A22A44A394",
  "7192068B345A",
  "72B3A5416980",
  "81A392010A91",
  "8940A52B1637",
  "A693542B7018",
  "A9425B168730",
  "AA023B723564",
  "B401638A2975",
  "B5861792A403",
];

//Choose one input randomly in sample inputs
get_random = function (list) {
  return list[Math.floor(Math.random() * list.length)];
};
let t1 = get_random(myarray);
// Split sampe inputs to change it into array
let array = t1.split("");
let array2 = t1.split("");
let arrcheck = array2.sort();
// Variable to highlight cell
let states = [];
let states2 = [];
let states3 = [];
// Variable to create new row
let generation = 0;
let generation2 = 0;
let generation3 = 0;
let w = 40; // pixel
let count = 0;
let status = 0;
let numcase = 0;
let setting = 0;
let values = [];
let values2 = [];
let values3 = [];

function setup() {
  createCanvas(1520, 1800);
  values = new Array(floor(480 / w));
  values2 = new Array(floor(480 / w));
  values3 = new Array(floor(480 / w));

  for (let i = 0; i < values.length; i++) {
    values[i] = array[i];
    states[i] = -1;
  }

  for (let i = 0; i < values2.length; i++) {
    values2[i] = array[i];
    states2[i] = -1;
  }

  for (let i = 0; i < values3.length; i++) {
    values3[i] = array[i];
    states3[i] = -1;
  }

  if (numcase == 0) {
    // Dispaly mergesort
    textSize(35);
    fill("black");
    text("Merge Sort", 100, 0, 300, 300);
    generation++;

    textSize(35);
    for (let j = 0; j < values.length; j++) {
      fill("black");
      text(values[j], j * w, w, w, w);
    }
    generation++;

    // Dispaly Gold's poresort
    textSize(35);
    fill("black");
    text("Gold's Poresort", 650, 0, 300, 300);
    generation2++;
    textSize(35);

    for (let j = values2.length + 1; j < values2.length * 2 + 1; j++) {
      fill("black");
      text(values[j - values2.length - 1], j * w, w, w, w);
    }
    generation2++;

    // Display Quicksort
    textSize(35);
    fill("black");
    text("Quicksort", 1200, 0, 300, 300);
    generation3++;
    textSize(35);

    for (let j = values3.length * 2 + 2; j < values3.length * 3 + 2; j++) {
      fill("black");
      text(values3[j - values3.length * 2 - 2], j * w, w, w, w);
    }
    generation3++;
  }
  numcase = 2;

  mergeSort(values);

  poreSort(values2);

  quickSort(values3, 0, values3.length - 1);
}

// MergeSort
function mergeSort(a) {
  arr = a.slice();

  mergeSortSlice(arr, 0, arr.length);
  return;
}

async function mergeSortSlice(arr, start, end) {
  if (end - start <= 1) {
    return;
  }

  var mid = Math.round((end + start) / 2);

  await mergeSortSlice(arr, start, mid);
  await mergeSortSlice(arr, mid, end);

  let i = start,
    j = mid;
  for (let i = start; i < mid; i++) {
    states[i] = 2;
  }

  while (i < end && j < end) {
    if (arraysAreIdentical(arr, arrcheck) == true) {
      break;
    }
    if (arr[i] > arr[j]) {
      setting = 0;
      await sleep(100);
      states[i] = 2;
      states[j] = 2;
      await sleep(100);

      await sleep(100);
      states[i] = 0;
      await sleep(100);
      states[j] = 1;

      let t = arr[j];
      arr.splice(j, 1);
      arr.splice(i, 0, t);

      j++;
    } else {
      setting = 1;
      await sleep(100);
      states[i] = 2;
      states[j] = 2;
      await sleep(100);
    }
    i++;
    if (i == j) {
      j++;
    }

    values = arr.slice();

    await sleep(100);
    if (setting == 0) generation++;
    await sleep(100);
    for (let i = 0; i < values.length; i++) {
      states[i] = -1;
    }
  }
}

function draw() {
  // Draw mergesort
  for (let i = 0; i < values.length; i++) {
    if (states[i] == 0) {
      fill("#E0777D");
      rect(i * w, generation * w, w, w);
      textSize(35);
      fill("red");
      text(values[i], i * w, generation * w, w, w);
    } else if (states[i] == 1) {
      fill("#D6FFB7");
      textSize(35);
      rect(i * w, w * generation, w, w);
      fill("blue");
      text(values[i], i * w, generation * w, w, w);
    } else if (states[i] == 2) {
      fill(100);
      textSize(35);
      rect(i * w, w * generation, w, w);
      fill("blue");
      text(values[i], i * w, generation * w, w, w);
    } else if (states[i] == -1) {
      textSize(35);
      fill(250);
      rect(i * w, w * generation, w, w);
      fill("pink");
      text(values[i], i * w, generation * w, w, w);
    }
  }

  //Draw Gold's poresort
  for (let i = values2.length + 1; i < values2.length * 2 + 1; i++) {
    if (states2[i - values2.length - 1] == 0) {
      fill("#E0777D");
      rect(i * w, generation2 * w, w, w);
      textSize(35);
      fill("red");
      text(values2[i - values2.length - 1], i * w, generation2 * w, w, w);
    } else if (states2[i - values2.length - 1] == 1) {
      fill("#D6FFB7");
      textSize(35);
      rect(i * w, w * generation2, w, w);
      fill("blue");
      text(values2[i - values2.length - 1], i * w, generation2 * w, w, w);
    } else if (states2[i - values2.length - 1] == 2) {
      fill(100);
      textSize(35);
      rect(i * w, w * generation2, w, w);
      fill("blue");
      text(values2[i - values2.length - 1], i * w, generation2 * w, w, w);
    } else if (states2[i - values2.length - 1] == -1) {
      textSize(35);
      fill(250);
      rect(i * w, w * generation2, w, w);
      fill("pink");
      text(values2[i - values2.length - 1], i * w, generation2 * w, w, w);
    }
  }
  //Draw Quicksort
  for (let i = values3.length * 2 + 2; i < values3.length * 3 + 2; i++) {
    if (states3[i - values3.length * 2 - 2] == 0) {
      fill("#E0777D");
      rect(i * w, generation3 * w, w, w);
      textSize(35);
      fill("red");
      text(values3[i - values3.length * 2 - 2], i * w, generation3 * w, w, w);
    } else if (states3[i - values3.length * 2 - 2] == 1) {
      fill("#D6FFB7");
      textSize(35);
      rect(i * w, w * generation3, w, w);
      fill("blue");
      text(values3[i - values3.length * 2 - 2], i * w, generation3 * w, w, w);
    } else if (states3[i - values3.length * 2 - 2] == 2) {
      fill("black");
      textSize(35);
      rect(i * w, w * generation3, w, w);
      fill("white");
      text(values3[i - values3.length * 2 - 2], i * w, generation3 * w, w, w);
    } else if (states3[i - values3.length * 2 - 2] == -1) {
      textSize(35);
      fill(250);
      rect(i * w, w * generation3, w, w);
      fill("pink");
      text(values3[i - values3.length * 2 - 2], i * w, generation3 * w, w, w);
    } else if (states3[i - values3.length * 2 - 2] == 3) {
      textSize(35);
      fill("green");
      rect(i * w, w * generation3, w, w);
      fill("pink");
      text(values3[i - values3.length * 2 - 2], i * w, generation3 * w, w, w);
    } else if (states3[i - values3.length * 2 - 2] == 4) {
      textSize(35);
      fill("yellow");
      rect(i * w, w * generation3, w, w);
      fill("pink");
      text(values3[i - values3.length * 2 - 2], i * w, generation3 * w, w, w);
    } else {
      fill(100);
      rect(i * w, w * generation3, w, w);
    }
  }
}

// Gold's poresort
async function poreSort(arr) {
  for (let i = 0; i < values2.length; i++) {
    if (count == arr.length) {
      console.log(count);
      break;
    }
    if (arraysAreIdentical(arr, arrcheck) == true) {
      break;
    }

    if (status == 0) {
      for (let j = 0; j < values2.length; j = j + 2) {
        await sleep(100);
        states2[j] = 2;
        states2[j + 1] = 2;
        await sleep(100);

        if (arr[j] > arr[j + 1]) {
          await sleep(100);
          states2[j] = 0;
          states2[j + 1] = 1;
          await sleep(50);
          await swap(arr, j, j + 1);
          await sleep(50);
          states2[j] = 1;
          states2[j + 1] = 0;
          status = 1;
          await sleep(100);
          generation2++;
          await sleep(100);
        } else {
          await sleep(100);
          states2[j] = 2;
          states2[j + 1] = 2;
          await sleep(100);
        }
        for (let i = 0; i < array.length; i++) {
          states2[i] = -1;
        }
      }
    } else if (status == 1) {
      for (let j = 1; j < values2.length; j = j + 2) {
        if (j != array.length - 1) {
          await sleep(100);
          states2[j] = 2;
          states2[j + 1] = 2;
          await sleep(100);

          if (arr[j] > arr[j + 1]) {
            await sleep(100);
            states2[j] = 0;
            states2[j + 1] = 1;
            await sleep(100);
            await swap(arr, j, j + 1);
            await sleep(100);
            states2[j] = 1;
            states2[j + 1] = 0;
            status = 0;
            await sleep(100);
            generation2++;
            await sleep(100);
          } else {
            await sleep(100);
            states2[j] = 2;
            states2[j + 1] = 2;
            await sleep(100);
          }
          for (let i = 0; i < array.length; i++) {
            states2[i] = -1;
          }
        }
      }
    }
    if (arraysAreIdentical(arr, arrcheck) == true) {
      break;
    }
    numcase = 2;
  }
}

// Quicksort
async function quickSort(arr, left, right) {
  let index;

  if (arr.length > 1) {
    left = typeof left != "number" ? 0 : left;
    right = typeof right != "number" ? arr.length - 1 : right;

    index = await partition(arr, left, right);

    if (left < index - 1) {
      await quickSort(arr, left, index - 1);
    }

    if (index < right) {
      await quickSort(arr, index, right);
    }
  }

  return arr;
}

let stopvar = 0;
async function partition(arr, left, right) {
  var pivot = arr[Math.floor((right + left) / 2)],
    i = left,
    j = right;
  while (i <= j) {
    states3[pivot] = 2;

    while (arr[i] < pivot) {
      i++;
    }

    while (arr[j] > pivot) {
      j--;
    }
    if (arraysAreIdentical(arr, arrcheck) == true) {
      for (let i = 0; i < values3.length; i++) {
        states[i] = 5;
      }
      i++;
      j--;
    } else if (i <= j && stopvar == 0) {
      await sleep(200);
      states3[i] = 1;
      states3[j] = 0;
      await sleep(200);
      await swap(arr, i, j);
      await sleep(200);
      states3[i] = 0;
      states3[j] = 1;
      i++;
      j--;

      await sleep(100);
      generation3++;
      await sleep(100);
    }
    for (let i = 0; i < array.length; i++) {
      states3[i] = -1;
    }
  }
  return i;
}

async function swap(arr, a, b) {
  await sleep(100);
  let temp = arr[a];
  arr[a] = arr[b];
  1;
  arr[b] = temp;
}

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

function arraysAreIdentical(arr1, arr2) {
  if (arr1.length !== arr2.length) return false;
  for (var i = 0, len = arr1.length; i < len; i++) {
    if (arr1[i] !== arr2[i]) {
      return false;
    }
  }
  return true;
}
