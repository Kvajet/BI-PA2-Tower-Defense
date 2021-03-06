#pragma once

#include "CEntity.h"
#include "CAstar.h"
#include <map>
#include <vector>
#include <memory>

/**
 * @class CEnemy
 * @brief Assigns death, damage to play and movement to enemy, returns map of actions to CGameLogic.
 * CEnemy is container for enemies, it is generated by CTokenEnemy class.
 */
class CEnemy : public CEntity
{
public:
    /**
     * @param[in] xPos 
     * @param[in] yPos 
     * @param[in] killValue     money player recieves after killing enemy
     * @param[in] damage 
     * @param[in] content       enemy look to be print
     * @param[in] HP 
     * @param[in] pathfinder    pathfinder class (CAstar)
     * @param[in] id            enemy ID for saving only
     */
    CEnemy( int xPos , int yPos , int killValue , int damage , char content , int HP , std::shared_ptr< CAstar > pathfinder , int id );
    /**
     * @brief map key is action to be proccessed, vector contains data for action (money for killing enemy, position to move, damage to deal), polymorphism
     * @return returns map with tags (defined integers in game_constants.cpp) and vectors
     */
    const std::map< int , std::vector< int > > & Action() override;
    /**
     * @param[in] damage damage taken by tower attack
     * @brief subtracts damage from HP
     */
    void RecieveDamage( int damage );
    /**
     * @param[out] os output stream (std::cout here)
     * @brief prints formatted enemy to console, overrides CField Print method, polymorphism
     */
    void Print( std::ostream & os ) const override;
    /**
     * @param[out] os output stream (std::cout here)
     * @brief method for saving to save file, overrides CEntity Save method, polymorphism
     */
    void Save( std::ofstream & os ) override;
    /**
     * @param[in] coords 
     * @brief compares CEnemy and given coordinates
     * @return yes - true / no - false
     */
    bool operator == ( const std::pair< int , int > & coords );
private:
    /**
     * @param[out] actionVec 
     * @brief adds enemy current position to actionVec (actionVec[0] = xPos, actionVec[1] = yPos)
     */
    void ActionPushPos( std::vector< int > & actionVec );
    /**
     * @param[out] actionVec 
     * @brief assigns that enemy is at end, to actionVec is assigned damaged value dealt to player (actionVec[2] = damage)
     */
    void ActionEnd( std::vector< int > & actionVec );
    /**
     * @param[out] actionVec 
     * @brief assigns from (m_path recieved from pathfinder) and to locations of enemy to actionVec
     * (actionVec[0] = xPos, actionVec[1] = yPos, actionVec[2] = toXPos, actionVec[3] = toYPos)
     */
    void ActionMove( std::vector< int > & actionVec );
    /**
     * @param[out] actionVec 
     * @brief assigns that enemy has died, to actionVec adds reward for player (actionVec[0] = killValue)
     */
    void ActionDeath( std::vector< int > & actionVec );
    /**
     * @param xPos 
     * @param yPos 
     * @brief changes current position to new one
     */
    void Move( int xPos , int yPos );
    int m_HP, m_damage, m_killValue;
    /** pathfinder pointer to get path from it */
    std::shared_ptr< CAstar > m_pathfinder;
    /** path used for movement, enemy uses always back value and pops it after use */
    std::list< std::pair< int , int > > m_path;
};
