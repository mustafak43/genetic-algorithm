# genetic-algorithm
Infinite Monkey Theorem solution using Genetic Algorithm in C++.

The one in the video was created in C#: 
https://www.youtube.com/watch?v=LkKNkx31vaE

Fitness evaluation works as follows:
- Index and the character at that index must match
    
Mutation works as follows:
- Each character of each string in the population has SET.MUT% chance to undergo mutation
    
Repopulation works as follows:
- Fittest offspring is found [best]
- The best is passed without modification to the next generation
- Either first or second half of the best is chosen randomly for each offspring based on the chance of getting crossovered [sample]
- Each offspring in the current generation does crossover with sample
- Mutation is applied to the new generation
