from Communicator import Communicator
from Renderer import Renderer
import json
import pygame

# Usage
if __name__ == "__main__":
    server_ip = "127.0.0.1"
    server_port = 8876

    renderer = Renderer()

    communicator = Communicator(server_ip, server_port)
    communicator.connect()

    while True:
        jsonMsg = communicator.recv_message().decode() 
        renderer.updateScreen(communicator.convertJsonToList(jsonMsg))
            
        left, middle, right = pygame.mouse.get_pressed()
        if left:
            print("+")
            communicator.send_message('+')
        elif right:
            print("-")
            communicator.send_message('-')
        else:    
            communicator.send_message('d')
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                communicator.send_message('exit')
                communicator.close()
                
                pygame.quit()
                
                exit()
                
                
            
        
            
            

        
        


    communicator.close()
