#include <iostream>
#include <vector>
#include <omp.h>

// Definici�n de estructuras para las especies
enum class Species { Empty, Plant, Herbivore, Carnivore };

struct Cell {
	Species species;
	int energy; // energ�a que tiene el ser vivo
};

using Grid = std::vector<std::vector<Cell>>;

// Par�metros de simulaci�n
const int grid_size = 10;
const int num_ticks = 100;
const int num_threads = 4;

// Inicializar la cuadr�cula con especies aleatorias
void initialize_grid(Grid& grid) {
	for (int i = 0; i < grid_size; ++i) {
		for (int j = 0; j < grid_size; ++j) {
			grid[i][j] = {Species::Empty, 0};
			if (rand() % 10 < 3) {
				grid[i][j] = {Species::Plant, 10}; // 30% probabilidad de planta
			} else if (rand() % 10 < 2) {
				grid[i][j] = {Species::Herbivore, 20}; // 20% probabilidad de herb�voro
			} else if (rand() % 10 < 1) {
				grid[i][j] = {Species::Carnivore, 30}; // 10% probabilidad de carn�voro
			}
		}
	}
}

// Funci�n para mostrar el estado del ecosistema
void print_grid(const Grid& grid) {
	for (const auto& row : grid) {
		for (const auto& cell : row) {
			char c = '.';
			switch (cell.species) {
			case Species::Plant: c = 'P'; break;
			case Species::Herbivore: c = 'H'; break;
			case Species::Carnivore: c = 'C'; break;
			default: break;
			}
			std::cout << c << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

// Actualizar el estado de cada celda
void update_cell(Cell& cell, Grid& grid, int x, int y) {
	switch (cell.species) {
	case Species::Plant:
		// Las plantas crecen
		cell.energy++;
		break;
	case Species::Herbivore:
		// Los herb�voros comen plantas y se mueven
		if (x > 0 && grid[x-1][y].species == Species::Plant) {
			cell.energy += grid[x-1][y].energy;
			grid[x-1][y] = {Species::Empty, 0};
		}
		cell.energy--; // consumo de energ�a al moverse
		break;
	case Species::Carnivore:
		// Los carn�voros comen herb�voros y se mueven
		if (x > 0 && grid[x-1][y].species == Species::Herbivore) {
			cell.energy += grid[x-1][y].energy;
			grid[x-1][y] = {Species::Empty, 0};
		}
		cell.energy--; // consumo de energ�a al moverse
		break;
	default:
		break;
	}
	if (cell.energy <= 0) {
		cell.species = Species::Empty; // el ser muere si no tiene energ�a
	}
}

// Ciclo principal de simulaci�n
void simulate(Grid& grid) {
	for (int tick = 0; tick < num_ticks; ++tick) {
		#pragma omp parallel for num_threads(num_threads)
		for (int i = 0; i < grid_size; ++i) {
			for (int j = 0; j < grid_size; ++j) {
				update_cell(grid[i][j], grid, i, j);
			}
		}
		// Sincronizar entre hilos (impl�cito con OpenMP)
		// Mostrar el estado del ecosistema
		std::cout << "Tick: " << tick << "\n";
		print_grid(grid);
	}
}

int main() {
	Grid grid(grid_size, std::vector<Cell>(grid_size));
	initialize_grid(grid);
	simulate(grid);
	return 0;
}