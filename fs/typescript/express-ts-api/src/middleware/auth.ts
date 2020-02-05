import * as jwt from 'jsonwebtoken';
import { Request, Response, NextFunction } from "express";
import * as ItemService from "../items/items.service";
import * as dotenv from "dotenv";

dotenv.config();

const auth = async (req : Request, res : Response, next : NextFunction) => {
	try{
		const token = req.header('Authorization').replace('Bearer ', '')
		const decoded = jwt.verify(token, process.env.JWT_SECRET)
        const user = await ItemService.find(_id: decoded._id)
	}
}