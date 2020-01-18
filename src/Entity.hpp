/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Entity.hpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:12:54 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 11:37:39 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ENTITY_HPP
# define ENTITY_HPP

#include <iostream>

class Entity
{
	private:
		Entity(void);
		Entity(Entity const &src);
		Entity &operator=(Entity const &src);

	protected:
		std::string		_type;
		char			_c;
		bool			_isAlive;
		unsigned int	_x;
		unsigned int	_y;

	public:
		~Entity(void);

		bool			getAlive(void);
		unsigned int	getX(void);
		unsigned int	getY(void);
		void			setDead(void);
		void			setX(unsigned int x);
		void			setY(unsigned int y);
		virtual void	updatePos(void) = 0;
};

#endif