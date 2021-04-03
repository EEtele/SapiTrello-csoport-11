# SapiTrello-csoport-11
Remélem ezt később lehet változtatni  
lehet.

## Commands
### Instance (Commands that can be used from anywhere)  
* Use keyboard combinations and arrows instead of commands  
	` ezMode`  
	
### User
* Create new user  
	` user new {userName} {userEmail}`  
* Delete user  
	` user delete {userEmail}`  

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
	` board user add {userEmail}`  
* Remove user from selected board  
	` board user remove {userEmail}`  

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
	` card user assign {cardID} {userEmail}`  
* Remove user from card  
	` card user remove {cardID} {userEmail}`  
* Return card status  
	` card status {cardID}`  
* Update card status  
	` card update {cardID}`  
* Set card status  
	` card update {cardID} {status}`  
* Return card log  
	` card log {cardID}`  
