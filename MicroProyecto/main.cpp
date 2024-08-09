#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

const int grid_size = 24;
const int num_ticks = 24;
const int num_threads = 12;

#define plant_spawn_rate     20 // porcentaje (int) de spawn
#define carnivore_spawn_rate 20 // porcentaje (int) de spawn
#define herbivore_spawn_rate 20 // porcentaje (int) de spawn

#define plant_reproduction_chance 0.15
#define carnivore_reproduction_energy 15
#define herbivore_reproduction_energy 15

#define plant_birth_energy     10
#define carnivore_birth_energy 10
#define herbivore_birth_energy 10

#define carnivore_birth_hunger 6 // muere despues de no comer por n ticks
#define herbivore_birth_hunger 3 // muere despues de no comer por n ticks

#define carnivore_energy_gain 3 // al comer herbívoro (grid[nx][ny].energy) para consumir la energía del herbívoro comido
#define herbivore_energy_gain 4 // al comer planta    (grid[nx][ny].energy) para consumir la energía de la planta comida

const int max_age = 10; // muerte por edad

enum struct Species { Empty, Plant, Herbivore, Carnivore };
struct Cell {
    Species species;
    int energy;
    int hunger;
    int age;
};
using Grid = vector<vector<Cell>>;

void initialize_grid(Grid& grid) {
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            grid[i][j] = {Species::Empty, 0};
            if (rand() % 100 < plant_spawn_rate) {
                grid[i][j] = {Species::Plant, plant_birth_energy};
            }
            if (rand() % 100 < carnivore_spawn_rate) {
                grid[i][j] = {Species::Carnivore, carnivore_birth_energy, carnivore_birth_hunger};
            }
            if (rand() % 100 < herbivore_spawn_rate) {
                grid[i][j] = {Species::Herbivore, herbivore_birth_energy, herbivore_birth_hunger};
            }
        }
    }
}

vector<pair<int, int>> get_neighbors(int x, int y) {
    vector<pair<int, int>> neighbors;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // ignorar la celda actual
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < grid_size && ny >= 0 && ny < grid_size) {
                neighbors.emplace_back(nx, ny);
            }
        }
    }
    return neighbors;
}

void update_cell(Cell& cell, Grid& grid, Grid& next_grid, const int& x, const int& y) {
    if (cell.species == Species::Empty) return;
    vector<pair<int, int>> neighbors = get_neighbors(x, y);
    switch (cell.species) {
        case Species::Plant: {
            for (auto& neighbor : neighbors) {
                int nx = neighbor.first;
                int ny = neighbor.second;
                if (grid[nx][ny].species == Species::Empty && (rand() % 100) < (plant_reproduction_chance * 100)) {
                    next_grid[nx][ny].species = Species::Plant;
                    next_grid[nx][ny].energy = plant_birth_energy;
                }
            }
            break;
        }
        case Species::Herbivore: {
            bool ate = false;
            for (auto& neighbor : neighbors) {
                int nx = neighbor.first;
                int ny = neighbor.second;
                if (grid[nx][ny].species == Species::Plant) {
                    next_grid[nx][ny].species = Species::Empty;
                    cell.energy += herbivore_energy_gain;
                    cell.hunger = herbivore_birth_hunger;
                    ate = true;
                    break;
                }
            }
            if (!ate) {
                cell.energy--;
            }

            if (cell.energy >= herbivore_reproduction_energy) {
                for (auto& neighbor : neighbors) {
                    int nx = neighbor.first;
                    int ny = neighbor.second;
                    if (next_grid[nx][ny].species == Species::Empty) {
                        next_grid[nx][ny].species = Species::Herbivore;
                        next_grid[nx][ny].energy = herbivore_birth_energy;
                        cell.hunger = herbivore_birth_hunger;
                        break;
                    }
                }
            }
            break;
        }
        case Species::Carnivore: {
            bool ate = false;
            for (auto& neighbor : neighbors) {
                int nx = neighbor.first;
                int ny = neighbor.second;
                if (grid[nx][ny].species == Species::Herbivore) {
                    next_grid[nx][ny].species = Species::Empty;
                    cell.energy += carnivore_energy_gain;
                    cell.hunger = carnivore_birth_hunger;
                    ate = true;
                    break;
                }
            }
            if (!ate) {
                cell.energy--;
            }

            if (cell.energy >= carnivore_reproduction_energy) {
                for (auto& neighbor : neighbors) {
                    int nx = neighbor.first;
                    int ny = neighbor.second;
                    if (next_grid[nx][ny].species == Species::Empty) {
                        next_grid[nx][ny].species = Species::Carnivore;
                        next_grid[nx][ny].energy = carnivore_birth_energy;
                        cell.hunger = carnivore_birth_hunger;
                        break;
                    }
                }
            }
            break;
        }
        default: break;
    }
    cell.age++;
    if (cell.energy <= 0 || cell.age > max_age) {
        next_grid[x][y].species = Species::Empty;
    } else {
        next_grid[x][y] = cell;
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
            char c = '.';
            switch (cell.species) {
            case Species::Plant:     c = 'P'; break;
            case Species::Herbivore: c = 'H'; break;
            case Species::Carnivore: c = 'C'; break;
            default: break;
            }
            cout << c << " ";
        }
    }
}

void simulate(Grid& grid) {
    for (int tick = 0; tick < num_ticks; ++tick) {
        Grid next_grid = grid;  // Crear una nueva cuadrícula para la próxima generación
        #pragma omp parallel for num_threads(num_threads)
        for (int i = 0; i < grid_size; ++i) {
            for (int j = 0; j < grid_size; ++j) {
                update_cell(grid[i][j], grid, next_grid, i, j);
            }
        }
        grid = next_grid;  // Actualizar la cuadrícula con la nueva generación
        cout << endl << endl << "Tick: " << tick + 1;
        print_grid(grid);
    }
}

int main() {
    Grid grid = Grid(grid_size, vector<Cell>(grid_size));
    initialize_grid(grid);
    simulate(grid);
    return 0;
}
