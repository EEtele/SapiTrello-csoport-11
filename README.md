# SapiTrello-csoport-11
Remélem ezt később lehet változtatni  
lehet.

## Commands
### Instance (Commands that can be used from anywhere)  
* Use keyboard combinations and arrows instead of commands  
	` ezMode`  
* Exit terminal in safe mode  
	` exit`  
	
#### Usage
* Please don't use `"` other than for parameters  

### User
* Create new user  
	` user new "userName" "userEmail"`  
* Delete user  
	` user delete "userEmail"`  
* List users  
	` user list`  

### Board  
* Create new Board  
	` Board new "boardName"`  
* Modify Board  
	` Board modify "boardName"`  
* Remove Board  
	` Board remove "boardName"`  
* List all boards  
	` Board list`  
* Select Board to work in  
	` Board select "boardName"`  
* Add user to Board to selected Board  
	` Board user add "userEmail"`  
* Remove user from selected Board  
	` Board user remove "userEmail"`  

### Card  
* Create new card  
	` card new "cardName" "cardDescription"`  
* Modify card  
	` card modify name "cardID" "cardName"`
	` card modify description "cardID" "cardDescription"  
* Remove card  
	` card remove "cardID"`  
* List all cards  
	` card list`  
* Assign user to card  
	` card user assign "cardID" "userEmail"`  
* Remove user from card  
	` card user remove "cardID" "userEmail"`  
* Print card status  
	` card status "cardID"`  
* Update card status  
	` card update "cardID"`  
* Set card status  
	` card update "cardID" "status"`  
* Print card log  
	` card log "cardID"`  
