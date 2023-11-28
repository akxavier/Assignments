import random
import string


def calculate_fitness(word):
    # Fitness is the number of adjacent characters that are the same
    return sum(1 for i in range(25) if word[i] == word[i + 1])


def select_parents(population, fitness_scores):
    total_fitness = sum(fitness_scores)
    probability_distribution = [
        score / total_fitness for score in fitness_scores]

    # Select two parents using roulette wheel selection
    parent1 = random.choices(population, weights=probability_distribution)[0]
    parent2 = random.choices(population, weights=probability_distribution)[0]

    return parent1, parent2


def crossover(parent1, parent2):
    # Choose a random crossover point
    crossover_point = random.randint(1, len(parent1) - 1)

    # Perform crossover
    child1 = parent1[:crossover_point] + parent2[crossover_point:]
    child2 = parent2[:crossover_point] + parent1[crossover_point:]

    return child1, child2


def mutate(word, mutation_rate):
    mutated_word = list(word)
    for i in range(len(mutated_word)):
        if random.random() < mutation_rate:
            mutated_word[i] = random.choice(string.ascii_lowercase)
    return ''.join(mutated_word)


def genetic_algorithm(population, population_size, generations, mutation_rate):

    for _ in range(generations):
        fitness_scores = [calculate_fitness(word) for word in population]

        new_population = []
        for _ in range(population_size // 2):
            parent1, parent2 = select_parents(population, fitness_scores)
            child1, child2 = crossover(parent1, parent2)
            child1 = mutate(child1, mutation_rate)
            child2 = mutate(child2, mutation_rate)
            new_population.extend([child1, child2])

        population = new_population

    best_word = max(population, key=calculate_fitness)
    print("\nBest word: {}\n".format(best_word))


if __name__ == "__main__":
    population_size = 4
    generations = 100
    user_words = [
        input(f"Enter word {i + 1}: ") for i in range(4)]

    mutation_rate = float(input('\nEnter Mutation Rate: '))

    genetic_algorithm(user_words, population_size,
                      generations, mutation_rate)
