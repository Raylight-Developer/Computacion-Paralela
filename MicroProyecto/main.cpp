#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

using namespace std;

const int grid_size = 64;
const int num_ticks = 1500;
const int tick_update = 100;
const int num_threads = 8;

#define plant_spawn_rate      0.3 // porcentaje de spawn
#define carnivore_spawn_rate  0.1 // porcentaje de spawn
#define herbivore_spawn_rate  0.1 // porcentaje de spawn

#define plant_after_spawn_rate     0.15  // porcentaje de spawn despues del inicio
#define carnivore_after_spawn_rate 0.05  // porcentaje de spawn despues del inicio
#define herbivore_after_spawn_rate 0.05  // porcentaje de spawn despues del inicio

#define plant_reproduction_chance 60
#define max_plant_age 150 // muerte por edad

#define carnivore_energy 30
#define herbivore_energy 25

#define carnivore_reproduction_energy 35
#define herbivore_reproduction_energy 45

#define carnivore_reproduction_energy_loss 25
#define herbivore_reproduction_energy_loss 35

#define carnivore_satiation 40
#define herbivore_satiation 20

#define carnivore_energy_gain 10 // al comer herbívoro (grid[nx][ny].energy) para consumir la energía del herbívoro comido
#define herbivore_energy_gain 5  // al comer planta    (grid[nx][ny].energy) para consumir la energía de la planta comida

#define max_carnivore_age 60 // muerte por edad
#define max_herbivore_age 80 // muerte por edad

enum struct Species { Empty, Plant, Herbivore, Carnivore };
struct Cell {
	Species species;
	int energy;
	int hunger;
	int age;

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
				update_cell(grid[i][j], grid, next_grid, i, j, random * i / (j+10) + tick);
			}
		}
		grid = next_grid;  // Actualizar la cuadrícula con la nueva generación
		if (tick % tick_update == 0) {
			cout << endl << endl << "Tick: " << tick + 1;
			print_grid(grid);
		}
	}
}

int main() {
	Grid grid = Grid(grid_size, vector<Cell>(grid_size));
	initialize_grid(grid);
	print_grid(grid);
	simulate(grid);
	return 0;
}
