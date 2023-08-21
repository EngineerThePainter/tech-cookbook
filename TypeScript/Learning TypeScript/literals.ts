// Literals are not only the strings, 
// but also their value is inferred to the type
const mathematician = "Mark Goldberg"

let lifespan: number | "ongoing" | "uncetain";
lifespan = 89;
lifespan = "ongoing"
// No - this is not part of the union
// lifespan = "deceased"
// Boolean is not part of the union
// lifespan = true