import { object, string } from 'zod'

export const signUpSchema = object({
    email: string({message: "Email is required"}).email("Invalid email"),
    password: string({message: "Password is required"})
        .min(8, "Password must be at least 8 characters")
        .max(32, "Password must be at most 32 characters"),
})

export const signInSchema = object({
    email: string({message: "Email is required"}).email("Invalid email"),
    password: string({message: "Password is required"})
})