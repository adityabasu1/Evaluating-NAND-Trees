# Evaluating-NAND-Trees

Algorithms Course Project at IIT Kharagpur (Spring'21)
## Presentation Recording <br />
https://drive.google.com/drive/folders/107NpMttpq6WPv3P7qxN7uX5ZEhwj1cZy?usp=sharing <br />
## Presentation Slides <br />
https://docs.google.com/presentation/d/1rY2m4XnHSgMjWz9YcYNvEA2jax_fOxgcJmw0LG8ctfg/edit?usp=sharing <br />
## Recap - NAND Gate  
A NAND gate is a logic gate that takes in two inputs and: 
- Evaluates to 0 if both its inputs are 1  
- Evaluates to 1 if either input is 0 

![hehe](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSlCHvQQYFf0kYpiO-wBRro3xBNK0Ag4n9SlDBsJGmZBuHMqp3JUW2fSmM0v1V7vk1gLlM&usqp=CAU)  
## What Is A NAND Tree?  
A NAND tree is a complete binary tree with the following properties:  
- Each leaf node is labelled either 0 or 1  
- All internal nodes are NAND gates  
  
This means that for any internal node (non-leaf node): ```node.value = (node.left_child) NAND (node.right_child)```  

An example:  


  ![hehe2](https://lh4.googleusercontent.com/H_x9UtZm6mXFLiK7Kv2MXLZS3ZqdjQMzQuHBKXVQV1j_7L3AWUN_CD_vh7LLemmZQXKTaKE9IxPMcFDLwHMl8Rd30D7japUPH7nnaAwPssbp6-phYdZrkbAk-MZ8jKMzsxz_rmNfFw)
## Algorithms on NAND Trees 
- Naive recursive algorithm (Linear)  
- Left-first algorithm (Linear in worst case)  
- Random-first algorithm (Sublinear)  
## Objective <br />
- Comparative running time analysis of the three algorithms on NAND Trees <br />
- Convergence of probabilities of random NAND Trees    
## Running the Code <br />
- Compilation: ```g++ Code_Evaluating_NAND_Trees.cpp``` <br />
- Execution: ```./a.out```<br />
## Input-Output <br />
On executing, you shall get this prompt:  
```Note that we'll have 2^k leaf nodes in the NAND trees```     
```Enter k:```    
 
**To Be Kept In Mind**  
- Total number of nodes in the perfect binary tree = 2^(k+1) - 1, where the tree has 2^k leaf nodes. 
- **DO NOT ENTER K MORE THAN 23**   
- k > 23 may lead to size shortage of data types  
- So, as a rule of thumb, ```0 <= k <= 23```

## Running Time    
- For ```k = 23``` running time would be around 15 seconds   
- So, in general, run time is not more than 15 seconds    









