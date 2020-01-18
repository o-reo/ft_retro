/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Player.hpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:47:32 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 13:12:24 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Entity.hpp"
# include <iostream>

class Player : public Entity
{
	public:
		Player(unsigned int x, unsigned int y);
		virtual ~Player(void);

		virtual void	updatePos(void);
};

#endif