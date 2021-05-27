# SapiTrello-csoport-11  
Yet another kanban-style, list-making Terminal application wroten in C.  
The program was wroten modularly to easily be able to change the interface to CLI or GUI.  


## Commands  

#### Usage  
* Please don't use `"` other than for parameters  
* Example:  
	` card modify name 13 "name"`  

### Instance (Commands that can be used from anywhere)  
* Exit terminal in safe mode (auto-save)  
	` exit`  
	
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
* Modify currently selected Board's name  
	` Board modify "boardName"`  
* Remove Board  
	` Board remove "boardName"`  
* List all boards  
	` Board list`  
* Select Board to work in  
	` Board select "boardName"`  
* Add user to Board to selected Board  
	` Board user add "userEmail"`  
* List all users in current boardName  
	` Board user list`  
* Remove user from selected Board  
	` Board user remove "userEmail"`  

### Card  
* Create new card  
	` card new "cardName" "cardDescription"`  
* Modify card  
	` card modify name {cardID} "cardName"`  
	` card modify description {cardID} "cardDescription"`  
* Remove card  
	` card remove {cardID}`  
* List all cards  
	` card list`  
* Group cards by status, then sort by datetime  
	` card sort`  
* Assign user to card  
	` card user assign {cardID} "userEmail"`  
* Remove user from card  
	` card user remove {cardID} "userEmail"`  
* Print card status  
	` card status {cardID}`  
* Update card status  
	` card update {cardID}`  
* Set card status (UpperCase)  
	` card update {cardID} "status"`  
* Print card log  
	` card log {cardID}`  
	
## Known bugs
* Whenever you can type but ">" is not present, just press ENTER.  
I think this is caused by flushing; if I were to not flush stdin, random syntax errors would appear because of dangling newlines)
