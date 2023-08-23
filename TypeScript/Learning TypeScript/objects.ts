type Poet = {
    name: string;
    born: number;
};

let poetObject: Poet;

poetObject = {
    name: "Sara Teasdale",
    born: 1935
};

console.log(poetObject.name);

type WithFirstName = {
    firstName: string;
};

type WithLastName = {
    lastName: string;
};

const hasBoth = {
    firstName: "Mark",
    lastName: "Clifford"
};

let withFirstName: WithFirstName = hasBoth;
let withLastName: WithLastName = hasBoth;

console.log(withFirstName);
console.log(withLastName);