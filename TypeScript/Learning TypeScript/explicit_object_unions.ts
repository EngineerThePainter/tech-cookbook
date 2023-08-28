type PoemWithPages = {
    name: string;
    pages: number;
};

type PoemWithRhymes = {
    name: string;
    rhymes: boolean;
}

type Poem = PoemWithPages | PoemWithRhymes;

const poem: Poem = Math.random() > 0.5 ? { name: "The Double Image", pages: 7 } : { name: "Her Kind", rhymes: true };

poem.name;
// This is not guaranteed to be there
// poem.pages;
// poem.rhymes;

// This will work however
if ("pages" in poem) {
    poem.pages;
} else {
    poem.rhymes;
}

// Intersection type:
type Artwork = {
    genre: string;
    name: string;
};

type Writing = {
    pages: number;
    name: string;
}

type WrittenArt = Artwork & Writing;

