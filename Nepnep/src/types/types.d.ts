declare module '*.css' {
    const content: { [className: string]: string }
    export default content
}

export type Color = {
    r: number
    g: number
    b: number
}

export type Camera = {
    x: number
    y: number
    zoom: number
}

export enum LayerType {
    Rectangle,
    Ellipse,
    Path,
    Text
}

export type RectangleLayer = {
    type: LayerType.Rectangle
    x: number
    y: number
    height: number
    width: number
    fill: Color
    stroke: Color
    opacity: number
    connerRadius: number
}

export type EllipseLayer = {
    type: LayerType.Ellipse
    x: number
    y: number
    height: number
    width: number
    fill: Color
    stroke: Color
    opacity: number
}

export type PathLayer = {
    type: LayerType.Path
    x: number
    y: number
    height: number
    width: number
    fill: Color
    stroke: Color
    opacity: number
    points: number[][]
}

export type TextLayer = {
    type: LayerType.Text
    x: number
    y: number
    height: number
    width: number
    fill: Color
    stroke: Color
    opacity: number
    text: string
    fontSize: number
    fontWidth: number
    fontFamily: string
}

export type Layer = RectangleLayer | EllipseLayer | PathLayer | TextLayer

export type Point = {
    x: number
    y: number
}