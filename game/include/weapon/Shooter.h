#pragma once

namespace ly {
	/* 
	* 1 ) Thinking who can own the weapon?
			Ans : Actor
      2 ) Consider how we implement shooting & weapon cool down mecahanism
	      - clock to counting time
		  - actual shoot action(ShootImpl()) to reset the clock
	 */
	class Actor;
	class Shooter {
	public:
		void Shoot();
		/* 
		 * This two virtual function is just a place holder for subclassing 
		 */
		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() const { return false; }
		Actor* GetOwner() { return mOwner; }
		int GetTeamId() const { return mTeamId; }
	protected:
		Shooter(Actor *ptrOwner);
	private:
		virtual void ShootImpl() = 0;
	private:
		Actor* mOwner;
		int mTeamId;
	};
}