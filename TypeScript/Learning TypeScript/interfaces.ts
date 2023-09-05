interface Poet {
    born: number;
    name: string;
}

let valueLater: Poet;

valueLater = {
    born: 1935,
    name: "Sara Teasdale"
}

// interface > aliased type object

interface Page {
    readonly text: string;
}

function read(page: Page) {
    console.log(page.text);
    // Not allowed
    // page.text = "text";
}

interface HasBothFunctionTypes {
    property: () => string;
    method(): string;
}

const hasBoth : HasBothFunctionTypes = {
    property: () => "property",
    method() {
        return "method";
    }
}

console.log(hasBoth.property());
console.log(hasBoth.method());

type FunctionAlias = (input: string) => number;
interface CallSignarure  {
    (input: string) => number;
}