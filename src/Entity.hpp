/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Entity.hpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:12:54 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 18:29:32 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>

class Entity
{
	protected:
		Entity(void);
		Entity(Entity const &src);
		Entity &operator=(Entity const &src);
		std::string		_type;
		std::string		_c;
		unsigned int	_nbLive;
		float			_x;
		float			_y;
		float			_dx;
		float			_dy;

public:
  virtual ~Entity(void);

		std::string		getType(void) const;
		std::string		getC(void) const;
		unsigned int	getNbLive(void) const;
		int				getX(void) const;
		int				getY(void) const;
		void			setNbLive(unsigned int nbLive);
		void			setX(int x);
		void			setY(int y);
		virtual void	updatePos(void) = 0;
};

#endif