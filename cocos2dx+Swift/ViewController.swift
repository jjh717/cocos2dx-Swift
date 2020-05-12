//
//  ViewController.swift
//  cocos2dx+Swift
//
//  Created by Jang Dong Min on 2020/05/12.
//  Copyright © 2020 Jang Dong Min. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    let cocosBridging = CocosBridging()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        self.view = cocosBridging.cocosScreenSetting(self.view)
        cocosBridging.runScene(self.view)
    }


}

