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

