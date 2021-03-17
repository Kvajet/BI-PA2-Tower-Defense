#pragma once

#include "CEntity.h"
#include <map>
#include <vector>

/**
 * @class CTower
 * @brief Assigns attack and special actions to tower, returns map of actions to CGameLogic.
 * CTower is tower container, it is generated by CTokenTower class in clone function and holds information
 * of turrets damage, range, fire rate.
 */
class CTower : public CEntity
{
public:
    /**
     * @param[in] xPos          X coordinate in map
     * @param[in] yPos          Y coordinate in map
     * @param[in] range         range of attack pattern
     * @param[in] fireDelay     cooldown for attack
     * @param[in] damage        damage dealt to enemies
     * @param[in] content       character representing tower
     * @param[in] attackType    attack type ID
     * @param[in] specialType   special type ID
     * @param[in] id            type of tower for saving
     */
    CTower( int xPos , int yPos , int range , int fireDelay , int damage , char content , int attackType , int specialType , int id );
    /**
     * @brief map key is action to be proccessed, vector contains data for action (coordinates to be attacked, amount of money to get, ...), polymorphism
     * @return returns map with tags (defined integers in game_constants.cpp) and vectors
     */
    const std::map< int , std::vector< int > > & Action() override;
    /**
     * @brief method for saving to save file, overrides CEntity Save method, polymorphism
     * @param[out] os   output file stream
     */
    void Save( std::ofstream & os ) override;
    /**
     * @brief prints formatted tower to console, overrides CField Print method, polymorphism
     * @param[out] os   output stream
     */
    void Print( std::ostream & os ) const override;
private:
    /**
     * @brief removes skip tag to enable tower's attack, performance optimalization
     */
    void RemoveSkipTag();
    /**
     * @brief adds skip tag to disable tower's attack, performance optimalization
     */
    void AddSkipTag();
    /**
     * @brief assigns attack to tower
     */
    void AssignAttack();
    /**
     * @brief assigns cross attack to tower, called by AssignAttack method
     * @param[out] actionVec    vector representing coordinates to be attacked
     * vector example: vec[0] = damage to be done, vec[1] = xPos, vec[2] = yPos, vec[3] = xPos, vec[4] = yPos, ...
     */
    void CrossAttack( std::vector< int > & actionVec );
    /**
     * @brief assigns area of effect attack to tower, called by AssignAttack method
     * @param[out] actionVec    vector representing coordinates to be attacked
     */
    void AOEAttack( std::vector< int > & actionVec );
    /**
     * @brief assigns special to tower
     */
    void AssignSpecials();
    /**
     * @brief assigns special that generates money every m_delayTime
     * @param[out] actionVec    vector representing amount to be generated
     * vector example: vec[0] = amount to be done (in future there can be for example HP to be restored, ...)
     * special action is then defined by map key value (TOWER_SPECIAL_GENERATE)
     */
    void GenerateSpecial( std::vector< int > & actionVec );
    /** range of tower's attack pattern */
    int m_range;
    /** cooldown of actions done by towers */
    int m_fireDelay;
    /** damage dealt to enemies */
    int m_damage;
    /** incremented every game tick, when equals to m_fireDelay tower may perform actions */
    int m_delayTimer = 0;
    /** tower's type of attack */
    int m_attackType;
    /** tower's type of special action */
    int m_specialAction = TOWER_SPECIAL_NONE;
    /** control if tower's attack was already set */
    bool m_attackSet = false;
};
