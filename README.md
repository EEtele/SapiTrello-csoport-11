# SapiTrello-csoport-11
Remélem ezt később lehet változtatni  
lehet.

## Commands
### Instance (Commands that can be used from anywhere)  
* Use keyboard combinations instead of commands  
	` ezMode`  
	
### User
* Create new user
	` user new {userName} {userEmail}`
* Delete user
	` user delete {userID}`

### Board  
* Create new board  
	` board new {boardName}`  
* Modify board  
	` board modify {boardName}`  
* Remove board  
	` board remove {boardName}`  
* List all boards  
	` board list`  
* Select board to work in  
	` board select {boardName}`  
* Add user to board to selected board  
	` board user add {userID}`  
* Remove user from selected board  
	` board user remove {userID}`  

### Card  
* Create new card  
	` card new {cardName}`  
* Modify card  
	` card modify {cardID}`  
* Remove card  
	` card remove {cardID}`  
* List all cards  
	` card list`  
* Assign user to card  
	` card user assign {cardID} {userID}`  
* Remove user from card  
	` card user remove {cardID} {userID}`  
* Return card status  
	` card status {cardID}`  
* Update card status  
	` card update {cardID}`  
* Set card status  
	` card update {cardID} {status}`  
* Return card log  
	` card log {cardID}`  