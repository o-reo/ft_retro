/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Entity.hpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:12:54 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 13:43:55 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ENTITY_HPP
# define ENTITY_HPP

#include <iostream>

class Entity
{
	protected:
		Entity(void);
		Entity(Entity const &src);
		Entity &operator=(Entity const &src);
		std::string		_type;
		char			_c;
		bool			_isAlive;
		unsigned int	_x;
		unsigned int	_y;

	public:
		virtual ~Entity(void);

		bool			getAlive(void) const;
		unsigned int	getX(void) const;
		unsigned int	getY(void) const ;
		void			setDead(void);
		void			setX(unsigned int x);
		void			setY(unsigned int y);
		virtual void	updatePos(void) = 0;
};

#endif