let arrayOfNumbers: number[];

arrayOfNumbers = [1,2,3,4,5,6];
arrayOfNumbers.push(1);
arrayOfNumbers.push(2);


// Type is either a string or an array of numbers
let stringOrArrayOfNumbers: string | number[];

// Type is an array of elements that are each either of string or number
let arrayOfStringOrNumbers: (string | number)[];

let twoDimensional: number[][];

twoDimensional = [[1,2,3],[4,5,6]];