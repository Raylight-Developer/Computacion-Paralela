/**
 * @file ecosystem_simulation.cpp
 * @brief Simulación de un ecosistema con plantas, herbívoros y carnívoros utilizando paralelización con OpenMP.
 */

#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

using namespace std;

/** Tamaño de la cuadrícula. */
const int grid_size = 60;
/** Número de iteraciones de la simulación. */
const int num_ticks = 1500;
/** Intervalo para imprimir el estado de la cuadrícula. */
const int tick_update = 250;
/** Número de hilos a utilizar en la simulación. */
const int num_threads = 12;

#define plant_spawn_rate      0.3  /**< Porcentaje de aparición inicial de plantas. */
#define carnivore_spawn_rate  0.1  /**< Porcentaje de aparición inicial de carnívoros. */
#define herbivore_spawn_rate  0.1  /**< Porcentaje de aparición inicial de herbívoros. */

#define plant_after_spawn_rate     0.15  /**< Porcentaje de aparición de plantas después del inicio. */
#define carnivore_after_spawn_rate 0.05  /**< Porcentaje de aparición de carnívoros después del inicio. */
#define herbivore_after_spawn_rate 0.05  /**< Porcentaje de aparición de herbívoros después del inicio. */

#define plant_reproduction_chance 60  /**< Probabilidad de reproducción de las plantas. */
#define max_plant_age 150 /**< Edad máxima de las plantas antes de morir. */

#define carnivore_energy 30  /**< Energía inicial de los carnívoros. */
#define herbivore_energy 25  /**< Energía inicial de los herbívoros. */

#define carnivore_reproduction_energy 35  /**< Energía requerida para que un carnívoro se reproduzca. */
#define herbivore_reproduction_energy 45  /**< Energía requerida para que un herbívoro se reproduzca. */

#define carnivore_reproduction_energy_loss 25  /**< Pérdida de energía al reproducirse para los carnívoros. */
#define herbivore_reproduction_energy_loss 35  /**< Pérdida de energía al reproducirse para los herbívoros. */

#define carnivore_satiation 40  /**< Nivel de hambre inicial de los carnívoros. */
#define herbivore_satiation 20  /**< Nivel de hambre inicial de los herbívoros. */

#define carnivore_energy_gain 15 + grid[nx][ny].energy  /**< Energía ganada por un carnívoro al comer un herbívoro. */
#define herbivore_energy_gain 10  /**< Energía ganada por un herbívoro al comer una planta. */

#define max_carnivore_age 60  /**< Edad máxima de los carnívoros antes de morir. */
#define max_herbivore_age 80  /**< Edad máxima de los herbívoros antes de morir. */

/**
 * @enum Species
 * @brief Define las especies posibles en la simulación.
 */
enum struct Species { Empty, Plant, Herbivore, Carnivore };

/**
 * @struct Cell
 * @brief Representa una célula en la cuadrícula, que puede contener una especie o estar vacía.
 */
struct Cell {
    Species species;  /**< Especie en la célula. */
    int energy;       /**< Energía de la célula. */
    int hunger;       /**< Nivel de hambre de la célula. */
    int age;          /**< Edad de la célula. */

    /**
     * @brief Constructor para inicializar una célula con una especie.
     * @param species Especie a la que pertenece la célula.
     */
	Cell(const Species& species = Species::Empty): species(species) {
		switch (species) {
			case Species::Empty: {
				energy = 0;
				hunger = 0;
				age = 0;
				break;
			}
			case Species::Plant: {
				energy = 0;
				hunger = 0;
				age = 0;
				break;
			}
			case Species::Herbivore: {
				energy = herbivore_energy;
				hunger = herbivore_satiation;
				age = 0;
				break;
			}
			case Species::Carnivore: {
				energy = carnivore_energy;
				hunger = carnivore_satiation;
				age = 0;
				break;
			}
		}
	}
};
using Grid = vector<vector<Cell>>;

/**
 * @brief Inicializa la cuadrícula con especies distribuidas aleatoriamente.
 * @param grid Cuadrícula a inicializar.
 */
void initialize_grid(Grid& grid) {
	for (int i = 0; i < grid_size; ++i) {
		for (int j = 0; j < grid_size; ++j) {
			grid[i][j] = Cell(Species::Empty);
			if (double(rand() % 100) < (plant_spawn_rate * 100.0)) {
				grid[i][j] = Cell(Species::Plant);
			}
			if (double(rand()*j % 100) < (carnivore_spawn_rate * 100.0)) {
				grid[i][j] = Cell(Species::Carnivore);
			}
			if (double(rand()*i % 100) < (herbivore_spawn_rate * 100.0)) {
				grid[i][j] = Cell(Species::Herbivore);
			}
		}
	}
}

/**
 * @brief Obtiene los vecinos de una posición en la cuadrícula.
 * @param x Coordenada x en la cuadrícula.
 * @param y Coordenada y en la cuadrícula.
 * @return Un vector de pares (x, y) que representan las posiciones vecinas.
 */
vector<pair<int, int>> get_neighbors(int x, int y) {
	vector<pair<int, int>> neighbors;
	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			if (dx == 0 && dy == 0) continue;
			int nx = x + dx;
			int ny = y + dy;
			if (nx >= 0 && nx < grid_size && ny >= 0 && ny < grid_size) {
				neighbors.emplace_back(nx, ny);
			}
		}
	}

	return neighbors;
}

/**
 * @brief Mueve una célula a una posición vacía en la cuadrícula.
 * @param neighbors Vecinos de la célula.
 * @param next_grid Cuadrícula para la siguiente iteración.
 * @param cell Célula que se va a mover.
 */
void move_to_empty(const vector<pair<int, int>>& neighbors, Grid& next_grid, Cell& cell) {
	for (const auto& neighbor : neighbors) {
		int nx = neighbor.first;
		int ny = neighbor.second;
		if (next_grid[nx][ny].species == Species::Empty) {
			next_grid[nx][ny] = cell;
			return;
		}
	}
}

/**
 * @brief Actualiza el estado de una célula en la cuadrícula.
 * @param current_cell Célula actual en la cuadrícula.
 * @param grid Cuadrícula actual.
 * @param next_grid Cuadrícula para la siguiente iteración.
 * @param x Coordenada x de la célula.
 * @param y Coordenada y de la célula.
 * @param random Número aleatorio utilizado para la actualización.
 */
void update_cell(const Cell& current_cell, const Grid& grid, Grid& next_grid, const int& x, const int& y, const int& random) {
	if (current_cell.species == Species::Empty) {
		if (random % 2 == 0) {
			if (double(random % 100) < (plant_after_spawn_rate * 100.0)) {
				next_grid[x][y] = Cell(Species::Plant);
			}
		}
		else if (random % 2 == 1) {
			if (double(random % 100) < (carnivore_after_spawn_rate * 100.0)) {
				next_grid[x][y] = Cell(Species::Carnivore);
			}
		}
		else if (random % 2 == 2) {
			if (double(random % 100) < (herbivore_after_spawn_rate * 100.0)) {
				next_grid[x][y] = Cell(Species::Herbivore);
			}
		}
	}

	vector<pair<int, int>> neighbors = get_neighbors(x, y);

	for (int i = neighbors.size() - 1; i > 0; --i) {
		int j = random % (i + 1);
		swap(neighbors[i], neighbors[j]);
	}

	switch (current_cell.species) {
		case Species::Plant: {
			if (current_cell.age > max_plant_age) {
				next_grid[x][y] = Cell(Species::Empty);
				break;
			}
			else {
				next_grid[x][y].age++;
			}
			for (auto& neighbor : neighbors) {
				int nx = neighbor.first;
				int ny = neighbor.second;
				if (grid[nx][ny].species == Species::Empty && double(random % 100) < (plant_reproduction_chance * 100.0)) {
					next_grid[nx][ny] = Cell(Species::Plant);
					break;
				}
			}
			break;
		}
		case Species::Herbivore: {
			if (current_cell.energy <= 0 || current_cell.age > max_herbivore_age || current_cell.hunger <= 0) {
				next_grid[x][y] = Cell(Species::Empty);
				break;
			}
			else {
				next_grid[x][y].age++;
			}
			bool ate = false;
			for (auto& neighbor : neighbors) {
				int nx = neighbor.first;
				int ny = neighbor.second;
				if (grid[nx][ny].species == Species::Plant) { // eat and move
					next_grid[nx][ny] = current_cell;
					next_grid[nx][ny].energy += herbivore_energy_gain;
					next_grid[nx][ny].hunger = herbivore_satiation;
					next_grid[x][y] = Cell(Species::Empty);
					ate = true;
					break;
				}
			}
			if (!ate) {
				next_grid[x][y].energy--;
				next_grid[x][y].hunger--;
				for (auto& neighbor : neighbors) {
					int nx = neighbor.first;
					int ny = neighbor.second;
					if (grid[nx][ny].species == Species::Empty) { // move
						next_grid[nx][ny] = current_cell;
						next_grid[x][y] = Cell(Species::Empty);
						break;
					}
				}
			}
			if (current_cell.energy >= herbivore_reproduction_energy) {
				for (auto& neighbor : neighbors) {
					int nx = neighbor.first;
					int ny = neighbor.second;
					if (next_grid[nx][ny].species == Species::Empty || next_grid[nx][ny].species == Species::Plant) {
						next_grid[nx][ny] = Cell(Species::Herbivore);
						next_grid[x][y].energy -= herbivore_reproduction_energy_loss;
						break;
					}
				}
			}
			break;
		}
		case Species::Carnivore: {
			if (current_cell.energy <= 0 || current_cell.age > max_carnivore_age || current_cell.hunger <= 0) {
				next_grid[x][y] = Cell(Species::Empty);
				break;
			}
			else {
				next_grid[x][y].age++;
			}
			bool ate = false;
			for (auto& neighbor : neighbors) {
				int nx = neighbor.first;
				int ny = neighbor.second;
				if (grid[nx][ny].species == Species::Herbivore) { // eat and move
					next_grid[nx][ny] = current_cell;
					next_grid[nx][ny].energy += carnivore_energy_gain;
					next_grid[nx][ny].hunger = carnivore_satiation;
					next_grid[x][y] = Cell(Species::Empty);
					ate = true;
					break;
				}
			}
			if (!ate) {
				next_grid[x][y].energy--;
				next_grid[x][y].hunger--;
				for (auto& neighbor : neighbors) {
					int nx = neighbor.first;
					int ny = neighbor.second;
					if (grid[nx][ny].species == Species::Empty) { // move
						next_grid[nx][ny] = current_cell;
						next_grid[x][y] = Cell(Species::Empty);
						break;
					}
				}
			}

			if (current_cell.energy >= carnivore_reproduction_energy) {
				for (auto& neighbor : neighbors) {
					int nx = neighbor.first;
					int ny = neighbor.second;
					if (next_grid[nx][ny].species == Species::Empty || next_grid[nx][ny].species == Species::Plant) {
						next_grid[nx][ny] = Cell(Species::Carnivore);
						next_grid[x][y].energy -= carnivore_reproduction_energy_loss;
						break;
					}
				}
			}
			break;
		}
		default: break;
	}
}

/**
 * @brief Imprime el estado actual de la cuadrícula, incluyendo el conteo de especies.
 * @param grid Cuadrícula a imprimir.
 */
void print_grid(const Grid& grid) {
	int plants = 0;
	int herbivores = 0;
	int carnivores = 0;
	for (const auto& row : grid) {
		for (const auto& cell : row) {
			switch (cell.species) {
				case Species::Plant: plants++; break;
				case Species::Herbivore: herbivores++; break;
				case Species::Carnivore: carnivores++; break;
				default: break;
			}
		}
	}
	cout << endl << "Plants: " << plants;
	cout << endl << "Herbivores: " << herbivores;
	cout << endl << "Carnivores: " << carnivores;

	for (const auto& row : grid) {
		cout << endl;
		for (const auto& cell : row) {
			string c = " ";
			switch (cell.species) {
				case Species::Plant:     c = "\033[92mP\033[0m"; break;
				case Species::Herbivore: c = "\033[94mH\033[0m"; break;
				case Species::Carnivore: c = "\033[91mC\033[0m"; break;
				default: break;
			}
			cout << c << " ";
		}
	}
}

/**
 * @brief Simula la evolución del ecosistema a lo largo del tiempo.
 * @param grid Cuadrícula que representa el ecosistema.
 */
void simulate(Grid& grid) {
	for (int tick = 0; tick < num_ticks; ++tick) {
		Grid next_grid = grid;  // Crear una nueva cuadrícula para la próxima generación
		srand(tick);
		int min = 1853087;
		int max = 153153150331;
		int random = min + std::rand() % (max - min + 1);
		#pragma omp parallel for num_threads(num_threads)
		for (int i = 0; i < grid_size; ++i) {
			for (int j = 0; j < grid_size; ++j) {
				update_cell(grid[i][j], grid, next_grid, i, j, random * i / (j + 10) * j + tick * i);
			}
		}
		grid = next_grid;  // Actualizar la cuadrícula con la nueva generación
		if (tick % tick_update == 0) {
			cout << endl << endl << "Tick: " << tick + 1;
			print_grid(grid);
		}
	}
}

/**
 * @brief Punto de entrada del programa. Inicializa y ejecuta la simulación.
 * @return Código de salida del programa.
 */
int main() {
	Grid grid = Grid(grid_size, vector<Cell>(grid_size));
	initialize_grid(grid);
	simulate(grid);
	return 0;
}