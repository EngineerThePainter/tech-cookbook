let mathematician: string | undefined;
mathematician = Math.random() > 0.5 ? undefined : "Goldberg";

let other_mathematician: string | null = null;
other_mathematician = "Marie"
// Not allowed
// other_mathematician = 51

let physicist = Math.random() > 0.5 ? "Marie Curie" : 0.5;

physicist.toString();
// Not allowed - not a member of number
// physicist.toUpperCase();
// Not allowed - not a member of String
// physicist.toFixed();

// Assignement Narrowing
let admiral: number | string;
admiral = "Grace Hooper"
// We can - at this moment TS knows during compilaton the type
admiral.toLowerCase();
// Nope
// admiral.toFixed();

// Conditional check

let scientist = Math.random() > 0.5
    ? "Rosalind Franklin"
    : 51;

if (scientist === "Rosalind Franklin") {
    // Type of scientist: string
    // TS knows at this moment the type MUST be string
    scientist.toUpperCase(); // Ok
}

// Type of scientist: number | string
// scientist.toUpperCase();

if (typeof scientist === "string") {
    // Type of scientist: string
    // TS knows at this moment the type MUST be string
    scientist.toUpperCase(); // Ok
}