/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:18:52 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/16 12:41:49 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"

int					State::width = 0;
int					State::height = 0;
int					State::size = 0;
std::u16string		State::solution;
score				State::solution_score = 0;
std::vector<int>	State::solution_finder;
score				State::initial_score = 0;
std::vector<int>	State::order;

State::State(const std::u16string &data) {
	_data = data;
	_weight = Heuristics::HeuristicFunction(_data, State::width);
	_distance = 0;
	_movement = None;
	_parent = nullptr;
}

State::State(State* parent, const State::Movement direction) {
	_data = parent->_data;
	_parent = parent;
	_distance = parent->_distance + 1;
	_movement = direction;

	int		new_pos = _data.find(static_cast<char16_t>(0));//the position that will be filled with the number
	int 	prev_pos;//the position that will be filled with the zero;
	int		w = State::width;
	
	switch (_movement)
	{
		case Up: prev_pos = new_pos - w; break ;
		case Left: prev_pos = new_pos - 1; break ;
		case Right: prev_pos = new_pos + 1; break ;
		case Down: prev_pos = new_pos + w; break ;
		case None: throw std::logic_error("None is not defined"); break;
	}
	//_weight =
	//		parent->get_weight() +
	//		Heuristics::HeuristicFunctionSwapper(_data, State::width, prev_pos, new_pos);
	std::swap(_data[new_pos], _data[prev_pos]);
	_weight = Heuristics::HeuristicFunction(_data, State::width);
}

std::vector<State::Movement>* State::get_movements() const {
	std::vector<State::Movement>* movements = new std::vector<State::Movement>(_distance);

	const State* node = this;
	int counter = _distance;

	while (--counter >= 0 && node)
	{
		(*movements)[counter] = node->_movement;
		node = node->_parent;
	}
	return (movements);
}

int State::get_distance() const
{
	return (_distance);
}

State::GridState State::is_solvable() const {
	std::u16string grid = _data;

	GridPoint posZero = GridPoint::GetPointFromIndex((int) grid.find(static_cast<char16_t >(0)), width);
	GridPoint destZero = GridPoint::GetPointFromIndex((int) solution.find(static_cast<char16_t >(0)), width);

	int distance = posZero.ManDistance(destZero);

	std::string::size_type index = 0;
	int moveCount = 0;
	while (index < grid.length()){
		char16_t solutionVal = solution[index];

		if (grid[index] != solutionVal)
		{
			std::string::size_type swapIndex = grid.find(solutionVal, index);
			if (swapIndex == std::string::npos)
			{
				return (State::GridState::MissingNum);
			}

			std::swap(grid[index], grid[swapIndex]);
			moveCount++;
		}
		index++;
	}

	if (moveCount % 2 == distance % 2){
		return (State::GridState::Valid);
	}
	return (State::GridState::Impossible);
}

bool State::is_final() const {
	return (_data == solution);
}

const std::u16string&	State::get_data(void) const
{
	return (this->_data);
}

bool			State::operator<(const State* b) const
{
	std::cout << "operator < of state" << std::endl;
	return  (_data == b->_data);
}

std::ostream& operator<< (std::ostream& s, const State::Movement c)
{
	if (c == State::Left)
		return (s << std::string("Left"));
	if (c == State::Right)
		return (s << std::string("Right"));
	if (c == State::Up)
		return (s << std::string("Up"));
	if (c == State::Down)
		return (s << std::string("Down"));
	return (s << std::string("None"));
}

void			State::set_parent(State* p)
{
	this->_parent = p;
}

State*			State::get_parent(void) const
{
	return (this->_parent);
}

void 			State::set_distance(int d)
{
	this->_distance = d;
}

score 						State::get_weight(void) const
{
	return (this->_weight);
}

void 						State::set_weight(score s)
{
	this->_weight = s;
}

State::Movement						State::get_movement() const {
	return (this->_movement);
}

std::vector<int> get_order(int w, int h)
{
	int orderIndex = 0;
	int				max = w * h;
	std::vector<int> order = std::vector<int>(max);
	char16_t		c = 1;
	int				pos = 0;
	State::Movement	dir = State::Right;
	std::u16string	data(max, static_cast<char16_t>('\0'));

	while (c <= max)
	{
		data[pos] = c;
		order[orderIndex++] = pos;
		++c;
		switch (dir)
		{
			case State::Right:
				++pos;
				if ((pos + 1) % w == 0 || data[pos + 1])
					dir = State::Down;
				break ;
			case State::Left:
				--pos;
				if (pos % w == 0 || data[pos - 1])
					dir = State::Up;
				break ;
			case State::Up:
				pos -= w;
				if (pos < w || data[pos - w])
					dir = State::Right;
				break ;
			case State::Down:
				pos += w;
				if (pos >= w * (h - 1) || data[pos + w])
					dir = State::Left;
				break ;
			default:
				break;
		}
	}
	return (order);
}

std::vector<int> gen_finder(std::u16string& sol)
{
	int     length = sol.length();
	std::vector<int> v(length);

	for (int i = 0; i < length; ++i)
		v[sol.at(i)] = i;
	return (v);
}
void			State::init(int width, int height)
{
	State::width = width;
	State::height = height;
	State::size = width * height;
	State::order = get_order(width, height);
	State::solution = Generator::gen_solution(width, height);
	State::solution_finder = gen_finder(State::solution);
	State::solution_score = Heuristics::HeuristicFunction(State::solution, width);
}

size_t custom_hash::operator()(const State* x) const noexcept
{
	//std::hash<std::u16string>	hash;
	//return (hash(x->get_data()));

	const char16_t* 	data = x->get_data().data();
	const char16_t*		end = data + State::size;
	size_t		value = 0;

	while (data < end)
	{
		value = 37 * value + *data;
		++data;
	}
	return (value);
}
bool custom_equal_to::operator()(const State* a, const State* b) const noexcept
{
	return (a->get_data() == b->get_data());
}
bool custom_less::operator()(const State* a, const State* b)
{
	//return ((a->get_weight()) > (b->get_weight()));
	return ((a->get_weight() + a->get_distance()) < (b->get_weight() + b->get_distance()));
}
